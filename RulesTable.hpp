#ifndef RULES_TABLE_HPP
#define RULES_TABLE_HPP

#include <boost/preprocessor/repetition.hpp> 
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include<map>
using namespace std;

#ifndef MAX_RULES_TABLE_PARAMS
#define MAX_RULES_TABLE_PARAMS 3
#endif

enum RulesTableReturn
{
	RULES_TABLE_NOT_FOUND = -1,
	RULES_TABLE_FOUND = 0,
	RULES_TABLE_FOUND_DEFAULT = 1
};
enum RulesTableStatus
{
	RULES_TABLE_STATUS_NO_DEFAULT, 
	RULES_TABLE_STATUS_WITH_DEFAULT
};

template<typename Value>
class RulesTable0 
{
public:
	void setRule(const Value& value)
	{
		_value = value;
	}
	
	int getRule(Value& value)
	{
		value = _value;
		return RULES_TABLE_FOUND;
	}

	friend templete<typename StreamType, typename Value>
	StreamType & operator << (StreamType& os, RulesTable0<Value>& rulesTable)
	{
		os << "=>\t" << rulesTable._value; 
		return os;
	}
	Value _value;
};

//terible thing begins
#define GEN_ARRAY_INDEX(z, n, key) [BOOST_PP_CAT(key, n)]


#define DECL_RULES_TABLE(z, n, unused) \
template <typename Value, BOOST_PP_ENUM_PARAMS(n, typename Key)> \
class BOOST_PP_CAT(RulesTable, n) \
{ \
public: \
typedef typename BOOST_PP_CAT(RulesTable, BOOST_PP_DEC(n))<Value BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_ENUM_SHIFTED_PARAMS(n, Key) >  SUB_MAP_TYPE;  \
\
	BOOST_PP_CAT(RulesTable, n)() \
		: _status(RULES_TABLE_STATUS_NO_DEFAULT) \
	{}\
\
	void setRule(BOOST_PP_ENUM_BINARY_PARAMS(n, const Key, &key), const Value& value)\
	{\
		_rules[key0].setRule(BOOST_PP_ENUM_SHIFTED_PARAMS(n, key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) value); \
	}\
\
	int getRule(BOOST_PP_ENUM_BINARY_PARAMS(n, const Key, &key), Value& value)\
	{\
		int ret = RULES_TABLE_NOT_FOUND; \
		map<Key0, typename SUB_MAP_TYPE>::iterator lb = _rules.lower_bound(key0); \
		if (lb != _rules.end()\
				&& key0 == lb->first)\
		{\
			ret = lb->second.getRule(BOOST_PP_ENUM_SHIFTED_PARAMS(n, key) BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) value); \
		}\
		else \
		{\
			ret = RULES_TABLE_NOT_FOUND; \
		}\
		if (RULES_TABLE_NOT_FOUND == ret && RULES_TABLE_STATUS_WITH_DEFAULT  == _status)\
		{\
			value = _value;\
			ret = RULES_TABLE_FOUND_DEFAULT; \
		}\
		return ret;\
	}\
\
	typename SUB_MAP_TYPE& operator[] (const Key0& key0) {return _rules[key0];} \
	map<Key0, typename SUB_MAP_TYPE> _rules; \
	Value _value; \
	int   _status; \
}; \

BOOST_PP_REPEAT_FROM_TO(1, MAX_RULES_TABLE_PARAMS, DECL_RULES_TABLE, ~)
//#define BOOST_PP_LOCAL_MACRO (n) DECL_RULES_TABLE(~, n, ~)
//#define BOOST_PP_LOCAL_LIMITS (1, MAX_RULES_TABLE_PARAMS)
//#include BOOST_PP_LOCAL_ITERATE()

#endif
