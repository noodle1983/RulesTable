#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic.hpp>

#include<map>
using namespace std;

#ifndef MAX_RULES_TABLE_PARAMS
#define MAX_RULES_TABLE_PARAMS 3
#endif

template<typename Value>
class RulesTable0 
{
public:
	typedef Value TYPE;
};

#define DECL_RULES_TABLE(z, n, unused) \
template <typename Value, BOOST_PP_ENUM_PARAMS(n, typename Key)> \
class BOOST_PP_CAT(RulesTable, n) \
{ \
public: \
typedef BOOST_PP_CAT(RulesTable, n)<Value, BOOST_PP_ENUM_PARAMS(n, Key) > TYPE;  \
typedef BOOST_PP_CAT(RulesTable, BOOST_PP_DEC(n))<Value BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_ENUM_SHIFTED_PARAMS(n, Key) >::TYPE  SUB_MAP_TYPE;  \
\
	map<Key0, SUB_MAP_TYPE> _rules; \
	Value* _value; \
}; \

BOOST_PP_REPEAT_FROM_TO(1, MAX_RULES_TABLE_PARAMS, DECL_RULES_TABLE, ~)
//#define BOOST_PP_LOCAL_MACRO (n) DECL_RULES_TABLE(~, n, ~)
//#define BOOST_PP_LOCAL_LIMITS (1, MAX_RULES_TABLE_PARAMS)
//#include BOOST_PP_LOCAL_ITERATE()

