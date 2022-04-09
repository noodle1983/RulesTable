#ifndef ENUMSTR_H
#define ENUMSTR_H

#include <iostream>
#include <string.h>
#include <map>

#define GET_MACRO(_1,_2,NAME,...) NAME
#define ADD_TO_ENUM1(name) name,
#define ADD_TO_ENUM2(name, value) name = value,
#define ADD_TO_ENUM(...) GET_MACRO(__VA_ARGS__,ADD_TO_ENUM2,ADD_TO_ENUM1)(__VA_ARGS__)

/**
 * ARRAY_STRINGABLE_ENUM start from 0, end with COUNT
 *
 */
#define ASSIGN_ENUM_ARRAY1(name) \
{\
    int value = prev_value + 1;\
    if(value < 0 || value >= N){ \
        std::cout << #name "'s value is out of range" << std::endl;\
    } \
    else { \
        if(nullptr != m_str_array[value]){ \
            std::cout << "!!!!!!!!!!enum[" #name "] value[" << value << "] is dupiclated with " \
                << m_str_array[value] << std::endl; \
        }else {\
            m_str_array[value] = #name;  \
        }\
    }\
    prev_value = value;\
}

#define ASSIGN_ENUM_ARRAY2(name, value) \
{\
    static_assert(value >= 0 && value < N, #name "'s value is out of range"); \
    if(nullptr != m_str_array[value]){ \
        std::cout << "!!!!!!!!!!enum[" #name "] value[" << value << "] is dupiclated with " \
            << m_str_array[value] << std::endl; \
    }else {\
        m_str_array[value] = #name;  \
    }\
    prev_value = value;\
}
#define ASSIGN_ENUM_ARRAY(...) GET_MACRO(__VA_ARGS__,ASSIGN_ENUM_ARRAY2,ASSIGN_ENUM_ARRAY1)(__VA_ARGS__)

#define ARRAY_STRINGABLE_ENUM_STR(ENUM_NAME, ENUM_VALUES)            \
template<unsigned N> struct _##ENUM_NAME{               \
    _##ENUM_NAME(){                                     \
        int prev_value = 0;                             \
        memset(m_str_array, 0, sizeof(m_str_array));    \
        ENUM_VALUES(ASSIGN_ENUM_ARRAY);                 \
        for(unsigned i = 0; i < N; i++) {               \
            if (nullptr == m_str_array[i]){             \
                m_str_array[i] = "not defined!";        \
            }                                           \
        }                                               \
    }                                                   \
    const char* m_str_array[N];                         \
};                                                      \
                                                        \
template<typename T> struct __##ENUM_NAME{              \
    static _##ENUM_NAME<T::MAX_COUNT> d;                \
};                                                      \
template<typename T>                                    \
_##ENUM_NAME<T::MAX_COUNT> __##ENUM_NAME<T>::d;         \
                                                        \
struct ENUM_NAME{                                       \
    enum{                                               \
        ENUM_VALUES(ADD_TO_ENUM)                        \
        MAX_COUNT                                       \
    };                                                  \
    typedef __##ENUM_NAME<ENUM_NAME> STRING;            \
    static const char* to_str(const int e){             \
        if (e < 0 || e >= MAX_COUNT) {                  \
            return "out of range";                      \
        }                                               \
        return STRING::d.m_str_array[e];                \
    }                                                   \
}; \

/**
 * GENERAL_STRINGABLE_ENUM end with COUNT
 */
#define ASSIGN_ENUM_GENERAL1(name) \
{\
    int value = prev_value + 1;\
    auto it = m_str_map.find(value); \
    if(it != m_str_map.end()){ \
        std::cout << "!!!!!!!!!!enum[" #name "] value[" << value << "] is dupiclated with " \
            << it->second << std::endl; \
    }else {\
        m_str_map[value] = #name;  \
    }\
    prev_value = value;\
}
#define ASSIGN_ENUM_GENERAL2(name, value) \
{\
    auto it = m_str_map.find(value); \
    if(it != m_str_map.end()){ \
        std::cout << "!!!!!!!!!!enum[" #name "] value[" << value << "] is dupiclated with " \
            << it->second << std::endl; \
    }else {\
        m_str_map[value] = #name;  \
    }\
    prev_value = value;\
}
#define ASSIGN_ENUM_GENERAL(...) GET_MACRO(__VA_ARGS__,ASSIGN_ENUM_GENERAL2,ASSIGN_ENUM_GENERAL1)(__VA_ARGS__)

#define GENERAL_STRINGABLE_ENUM_STR(ENUM_NAME, ENUM_VALUES)            \
struct _##ENUM_NAME{                                    \
    _##ENUM_NAME(){                                     \
        int prev_value = 0;                             \
        m_str_map.clear();                              \
        ENUM_VALUES(ASSIGN_ENUM_GENERAL);               \
    }                                                   \
    std::map<int, const char*> m_str_map;               \
};                                                      \
                                                        \
template<typename T> struct __##ENUM_NAME{              \
    static _##ENUM_NAME d;                              \
};                                                      \
template<typename T>                                    \
_##ENUM_NAME __##ENUM_NAME<T>::d;                       \
                                                        \
struct ENUM_NAME{                                       \
    enum{                                               \
        ENUM_VALUES(ADD_TO_ENUM)                        \
        MAX_COUNT                                       \
    };                                                  \
    typedef __##ENUM_NAME<ENUM_NAME> STRING;            \
    static const char* to_str(const int e){             \
        auto& str_map = STRING::d.m_str_map;            \
        auto it = str_map.find(e);                      \
        if (it == str_map.end()) {                      \
            return "not defined!";                      \
        }                                               \
        return it->second;                              \
    }                                                   \
}; 


//----------------------test-----------------------------
#define TestArrayEnumValues(MACRO) \
    MACRO(val1, 1) \
    MACRO(val2) \
    MACRO(val3, 3)

ARRAY_STRINGABLE_ENUM_STR(TestArrayEnum, TestArrayEnumValues)

#define TestGeneralEnumValues(MACRO) \
    MACRO(val1, -1) \
    MACRO(val2) \
    MACRO(val3, 3)

GENERAL_STRINGABLE_ENUM_STR(TestGeneralEnum, TestGeneralEnumValues)


#endif /* ENUMSTR_H */

