#ifndef SPARSE_TABLE_HPP
#define SPARSE_TABLE_HPP

#include <boost/preprocessor/repetition.hpp> 
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/comparison/greater_equal.hpp>

#include <unordered_map>
#include <sstream>

#ifndef MAX_SPARSE_TABLE_PARAMS
#define MAX_SPARSE_TABLE_PARAMS 4 
#endif

/**
class SparseTableN{
    clear();                   // clear all in map and reset default value;
    ...                        // clear on level n
    clear(key0, keyn);         // clear value on the leaf

    set(v);                    // set top default value, leave the map untouched.
    ...                        // set the level n default value, leave the map untouched
    set(key0, keyn, v);        // set the value on the leaf
    set_leaf(key0-n, v);       // set the value on the leaf

    get();                     // get top default value, leave the map untouched.
    ...                        // get the level n default value, leave the map untouched
    get(key0, keyn);           // get the value on the leaf
    get_leaf(key0-n);          // set the value on the leaf

    operator[]                 // get/set the default value if not enough key, or leaf value
}
 */

enum SparseTableReturn
{
	SPARSE_TABLE_NOT_FOUND = -1,
	SPARSE_TABLE_FOUND = 0,
	SPARSE_TABLE_FOUND_DEFAULT = 1
};


template < typename Key0, typename Value >
class SparseTable1 {
public:
    using SELF_TYPE = SparseTable1 < Key0, Value > ;
    using SUB_MAP_TYPE = Value;

public:
    SparseTable1() {}
    void clear() { _t.clear(); _def = {}; }
    void clear(const Key0 & key0) { _t.erase(key0); }

	void set(const Value& value) { _def = value; }
	void set(Value&& value) { _def = value; }
	void set(const Key0& key0, const Value& value) { if(value == _def){ clear(key0); } else {_t[key0] = value;} }
	void set(const Key0& key0, Value&& value) { if(value == _def){ clear(key0); } else {_t[key0] = value;} }
	void set_leaf(const Key0& key0, const Value& value) { if(value == _def){ clear(key0); } else {_t[key0] = value;} }
	void set_leaf(const Key0& key0, Value&& value) { if(value == _def){ clear(key0); } else {_t[key0] = value;} }

	Value get() const { return _def; }
	int get(Value& value) { value = _def; return SPARSE_TABLE_FOUND_DEFAULT; }
    int get(const Key0 & key0, Value & value) {
        auto lb = _t.find(key0);
        if (lb != _t.end()) {
            value = lb->second;
            return SPARSE_TABLE_FOUND;
        }
        value = _def;
        return SPARSE_TABLE_FOUND_DEFAULT;
    }
    Value get(const Key0 & key0) {
        Value value;
        get(key0, value);
        return value;
    }
    int get_leaf(const Key0 & key0, Value & value) { return get(key0, value); }
    Value get_leaf(const Key0 & key0) { return get(key0); }

    SUB_MAP_TYPE & operator[](const Key0 & key0) {
        return _t[key0];
    }

    template < typename StreamType >
    friend StreamType & operator << (StreamType & os, SparseTable1 < Key0, Value > & sparseTable) {
        std::ostringstream ostr;
        sparseTable.toString(ostr, 0, nullptr);
        os << ostr.str();
        return os;
    }
    void toString(std::ostringstream & os, int nTab, Value * value) {
        if (nullptr != value) {
            toDefaultString(os, nTab, value);
            return;
        }
        int first = 1;
        auto it = _t.begin();
        auto end = _t.end();
        for (; it != end; it++) {
            if (!first) {
                for (int i = 0; i < nTab; i++) {
                    os << "[^]\t";
                }
            }
            os << "[" << it->first << "]\t" << "=>\t[" << it->second << "]" << std::endl;
            first = 0;
        } 
        {
            if (!first) {
                for (int i = 0; i < nTab; i++) {
                    os << "[^]\t";
                }
            }
            toDefaultString(os, nTab, & _def);
        }
    }
    static void toDefaultString(std::ostringstream & os, int nTab, Value * value) {
        if (nullptr != value) {
            os << "[N/A]\t=>\t[" << *value << "]" << std::endl;
        }
        else {
            os << "[N/A]\t=>\tnullptr" << std::endl;
        }
    }
    void setDefaultRule(const Value & value) {
        _def = value;
    }

private: 
    std::unordered_map < Key0, SUB_MAP_TYPE > _t;
    Value _def = {};
};


//terible thing begins

//clear value
#define DECL_CLEAR(z, m, unused) \
	void clear(BOOST_PP_ENUM_BINARY_PARAMS(m, const Key, &key)) {\
		BOOST_PP_IF(m, \
		BOOST_PP_IDENTITY(_t[key0].clear(BOOST_PP_ENUM_SHIFTED_PARAMS(m, key));), \
		BOOST_PP_IDENTITY(_t.clear(); _def = {};))()\
	}

//set value
#define DECL_SET(z, m, unused) \
	void set(BOOST_PP_ENUM_BINARY_PARAMS(m, const Key, &key) BOOST_PP_COMMA_IF(m) const Value& value) {\
		BOOST_PP_IF(m, \
		BOOST_PP_IDENTITY(_t[key0].set(BOOST_PP_ENUM_SHIFTED_PARAMS(m, key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(m)) value );), \
		BOOST_PP_IDENTITY(_def = value;))()\
	}\
	void set(BOOST_PP_ENUM_BINARY_PARAMS(m, const Key, &key) BOOST_PP_COMMA_IF(m) Value&& value) {\
		BOOST_PP_IF(m, \
		BOOST_PP_IDENTITY(_t[key0].set(BOOST_PP_ENUM_SHIFTED_PARAMS(m, key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(m)) value );), \
		BOOST_PP_IDENTITY(_def = value;))()\
	}

//get value
#define DECL_GET(z, m, unused) \
    int get(BOOST_PP_ENUM_BINARY_PARAMS(m, const Key, &key) BOOST_PP_COMMA_IF(m) Value& value) {\
        BOOST_PP_IF(m, \
        BOOST_PP_IDENTITY( \
            auto lb = _t.find(key0); \
            if (lb != _t.end()) {\
                return lb->second.get(BOOST_PP_ENUM_SHIFTED_PARAMS(m, key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(m)) value); \
            }\
            value = _def;\
            return SPARSE_TABLE_FOUND_DEFAULT; \
        ), \
        BOOST_PP_IDENTITY( value = _def; return SPARSE_TABLE_FOUND_DEFAULT; ))()\
    }\
	Value get(BOOST_PP_ENUM_BINARY_PARAMS(m, const Key, &key)) \
	{\
		Value value;\
		get(BOOST_PP_ENUM_PARAMS(m, key) BOOST_PP_COMMA_IF(m) value);\
		return value;\
	}

//proxy get value
#define DECL_PROXY_GET(z, m, unused) \
    BOOST_PP_EXPR_IF( BOOST_PP_GREATER_EQUAL(m, 2), \
        Value get(BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(m, const Key, &key)) {\
            return _parent->get(_key BOOST_PP_COMMA_IF(BOOST_PP_DEC(m)) BOOST_PP_ENUM_SHIFTED_PARAMS(m, key));\
        }\
    ) \

//proxy set value
#define DECL_PROXY_SET(z, m, unused) \
    BOOST_PP_EXPR_IF( BOOST_PP_GREATER_EQUAL(m, 2), \
        void set(BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(m, const Key, &key) BOOST_PP_COMMA_IF(m) const Value& value) {\
            _parent->set(_key, BOOST_PP_ENUM_SHIFTED_PARAMS(m, key) BOOST_PP_COMMA_IF(m) value);\
        }\
        void set(BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(m, const Key, &key) BOOST_PP_COMMA_IF(m) Value&& value) {\
            _parent->set(_key, BOOST_PP_ENUM_SHIFTED_PARAMS(m, key) BOOST_PP_COMMA_IF(m) value);\
        } \
    ) \

//proxy type
template < typename SparseTableOrProxy, typename Value > \
class SparseSubTableProxy0 {};

#define DECL_PROXY_TABLE(z, n, unused) \
template < typename SparseTableOrProxy, BOOST_PP_ENUM_PARAMS(n, typename Key), typename Value > \
class BOOST_PP_CAT(SparseSubTableProxy, n) {\
public: \
    using TABLE_TYPE = SparseTableOrProxy; \
    using SELF_TYPE = BOOST_PP_CAT(SparseSubTableProxy, n)<SparseTableOrProxy, BOOST_PP_ENUM_PARAMS(n, Key), Value > ;  \
    using CUR_KEY = Key0; \
 \
    BOOST_PP_CAT(SparseSubTableProxy, n)(TABLE_TYPE* tbl, const CUR_KEY& key) \
        : _parent(tbl), _key(key){} \
    virtual ~BOOST_PP_CAT(SparseSubTableProxy, n)(){} \
 \
BOOST_PP_REPEAT(BOOST_PP_INC(n), DECL_PROXY_GET, ~)\
BOOST_PP_REPEAT(BOOST_PP_INC(n), DECL_PROXY_SET, ~)\
 \
    operator Value() {return _parent->get(_key);} \
    Value operator = (const Value& value){ _parent->set(_key, value); return value;} \
    Value operator = (Value&& value){ _parent->set(_key, value); return value;} \
     \
using SUB_MAP_TYPE = BOOST_PP_CAT(SparseSubTableProxy, BOOST_PP_DEC(n))<SELF_TYPE, BOOST_PP_ENUM_SHIFTED_PARAMS(n, Key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) Value > ;  \
    BOOST_PP_EXPR_IF( BOOST_PP_GREATER_EQUAL(n, 2), \
        SUB_MAP_TYPE operator[](const Key1& key) { \
            return SUB_MAP_TYPE(this, key); \
        }\
    )\
	template <typename StreamType> \
	friend StreamType & operator << (StreamType& os, const SELF_TYPE& table)\
	{\
		return os << table._parent->get(table._key);\
	}\
\
private:  \
    TABLE_TYPE* _parent; \
    const CUR_KEY& _key; \
}; 
BOOST_PP_REPEAT_FROM_TO(1, MAX_SPARSE_TABLE_PARAMS, DECL_PROXY_TABLE, ~); 

#define DECL_SPARSE_TABLE(z, n, unused) \
template <BOOST_PP_ENUM_PARAMS(n, typename Key), typename Value> \
class BOOST_PP_CAT(SparseTable, n) \
{ \
public: \
    using SELF_TYPE = BOOST_PP_CAT(SparseTable, n)<BOOST_PP_ENUM_PARAMS(n, Key), Value > ;  \
    using SUB_MAP_TYPE = BOOST_PP_CAT(SparseTable, BOOST_PP_DEC(n))<BOOST_PP_ENUM_SHIFTED_PARAMS(n, Key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) Value > ;  \
    using PROXY_TYPE = BOOST_PP_CAT(SparseSubTableProxy, n)<SELF_TYPE, BOOST_PP_ENUM_PARAMS(n, Key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) Value > ;  \
\
public: \
\
	BOOST_PP_CAT(SparseTable, n)() {}\
\
    BOOST_PP_REPEAT(BOOST_PP_INC(n), DECL_CLEAR, ~)\
\
    BOOST_PP_REPEAT(BOOST_PP_INC(n), DECL_SET, ~)\
	void set_leaf(BOOST_PP_ENUM_BINARY_PARAMS(n, const Key, &key), const Value& value){ set(BOOST_PP_ENUM_PARAMS(n, key), value);}\
	void set_leaf(BOOST_PP_ENUM_BINARY_PARAMS(n, const Key, &key), Value&& value){ set(BOOST_PP_ENUM_PARAMS(n, key), value);}\
\
    BOOST_PP_REPEAT(BOOST_PP_INC(n), DECL_GET, ~)\
	int get_leaf(BOOST_PP_ENUM_BINARY_PARAMS(n, const Key, &key), Value&& value){ get(BOOST_PP_ENUM_PARAMS(n, key), value);}\
	Value get_leaf(BOOST_PP_ENUM_BINARY_PARAMS(n, const Key, &key)){ get(BOOST_PP_ENUM_PARAMS(n, key));}\
\
	PROXY_TYPE operator[] (const Key0& key0) {return PROXY_TYPE(this, key0);} \
\
	template <typename StreamType> \
	friend StreamType & operator << (StreamType& os, BOOST_PP_CAT(SparseTable, n)<BOOST_PP_ENUM_PARAMS(n, Key), Value>& sparseTable)\
	{\
		std::ostringstream ostr;\
		sparseTable.toString(ostr, 0, NULL);\
		os << ostr.str();\
		return  os;\
	}\
	void toString(std::ostringstream& os, int nTab, Value* value)\
	{\
		if (NULL != value) \
		{\
			toDefaultString(os, nTab, value);\
			return;\
		}\
		int first = 1;\
		typename std::unordered_map<Key0, SUB_MAP_TYPE>::iterator it = _t.begin();\
		typename std::unordered_map<Key0, SUB_MAP_TYPE>::iterator end = _t.end();\
		for(;it != end; it++) \
		{\
			if (!first)\
			{\
				for(int i = 0; i < nTab; i++){os << "[^]\t"; }\
			}\
			os << "[" << it->first <<"]\t";\
			it->second.toString(os, nTab + 1, value);\
			first = 0;\
		}\
		{\
			if (!first)\
			{\
				for(int i = 0; i < nTab; i++){os << "[^]\t"; }\
			}\
			toDefaultString(os, nTab, &_def);\
		}\
	}\
	static void toDefaultString(std::ostringstream& os, int nTab, Value* value)\
	{\
		os << "[N/A]\t";\
		SUB_MAP_TYPE::toDefaultString(os, nTab + 1, value);\
	}\
\
private:\
	std::unordered_map<Key0, SUB_MAP_TYPE> _t; \
	Value _def = {}; \
}; \

BOOST_PP_REPEAT_FROM_TO(2, MAX_SPARSE_TABLE_PARAMS, DECL_SPARSE_TABLE, ~)
//#define BOOST_PP_LOCAL_MACRO (n) DECL_SPARSE_TABLE(~, n, ~)
//#define BOOST_PP_LOCAL_LIMITS (1, MAX_SPARSE_TABLE_PARAMS)
//#include BOOST_PP_LOCAL_ITERATE()

#endif
