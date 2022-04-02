#ifndef ENUMSTR_H
#define ENUMSTR_H

#include <iostream>
#include <string.h>

#define ADD_TO_ENUM(name, value) name = value,

/**
 * ARRAY_STRINGABLE_ENUM start from 0, end with COUNT, consecutively
 * define example:
 *     #define TestEnumValues(MACRO) \
 *         MACRO(val1, 1) \
 *         MACRO(val2, 1) \
 *         MACRO(val4, 3)
 *     ARRAY_STRINGABLE_ENUM_STR(TestEnum, TestEnumValues)
 *
 * usage example:
 *     void print_str(){
 *         for(int i = -1; i < TestEnum::MAX_COUNT + 1; i++) {
 *             cout << i << ":"  << TestEnum::to_str(i) << endl;
 *         }
 *     }
 * output:
 * !!!!!!!!!!enum[val2] value[1] is dupiclated with val1
 * -1:out of range
 * 0:not defined!
 * 1:val1
 * 2:not defined!
 * 3:val4
 * 4:out of range
 *
 */
#define ASSIGN_ENUM_ARRAY(name, value) \
    static_assert(value >= 0 && value < N, #name "'s value is out of range"); \
    if(nullptr != m_str_array[value]){ \
        std::cout << "!!!!!!!!!!enum[" #name "] value[" << value << "] is dupiclated with " \
            << m_str_array[value] << std::endl; \
    }else {\
        m_str_array[value] = #name;  \
    }

#define ARRAY_STRINGABLE_ENUM_STR(ENUM_NAME, ENUM_VALUES)            \
template<unsigned N> struct _##ENUM_NAME{               \
    _##ENUM_NAME(){                                     \
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
    static _##ENUM_NAME<T::MAX_COUNT> d;          \
};                                                      \
template<typename T>                                    \
_##ENUM_NAME<T::MAX_COUNT> __##ENUM_NAME<T>::d;      \
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


//----------------------test-----------------------------
#define TestEnumValues(MACRO) \
    MACRO(val1, 1) \
    MACRO(val2, 1) \
    MACRO(val4, 3)

ARRAY_STRINGABLE_ENUM_STR(TestEnum, TestEnumValues)

#endif /* ENUMSTR_H */

