#include "enumstr.h"
#include <iostream>


using namespace std;
int print_array_enum_str(){
    cout << "array_enum:" << endl;
    for(int i = -1; i < TestArrayEnum::MAX_COUNT + 1; i++) {
        cout << i << ":"  << TestArrayEnum::to_str(i) << endl;
    }
    return 0;
}
int print_general_enum_str(){
    cout << "general_enum:" << endl;
    for(int i = -1; i < TestGeneralEnum::MAX_COUNT + 1; i++) {
        cout << i << ":"  << TestGeneralEnum::to_str(i) << endl;
    }
    return 0;
}

int main(){
    print_array_enum_str();
    cout << endl;
    print_general_enum_str();
    return 0;
}

