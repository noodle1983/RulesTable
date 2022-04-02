#include "enumstr.h"
#include <iostream>


using namespace std;
int print_str(){
    for(int i = -1; i < TestEnum::MAX_COUNT + 1; i++) {
        cout << i << ":"  << TestEnum::to_str(i) << endl;
    }
    return 0;
}

int main(){
    print_str();
    return 0;
}

