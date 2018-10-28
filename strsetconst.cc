#include <iostream>

#include "strset.h"
    
#ifndef NDEBUG 
    const bool debug = true;
#else 
    const bool debug = false;
#endif


// AUXILIARY FUNCTIONS

unsigned long& strset42_id() {
    static unsigned long strset42_id = 0;
    return strset42_id;
}

void print_info() {
    if (!debug) return;
    
    std::ios_base::Init();
    std::cerr << "strsetconst init invoked" << std::endl;
}

void print_result() {
    if (!debug) return;
    
    std::ios_base::Init();
    std::cerr << "strsetconst init finished" << std::endl;
}

namespace jnp1 {
extern "C" {
    // STRSET FUNCTIONS

    //Zwraca identyfikator zbioru, którego nie można modyfikować i który zawiera
    //jeden element: napis "42". Zbiór jest tworzony przy pierwszym wywołaniu tej
    //funkcji i wtedy zostaje ustalony jego numer.
    unsigned long strset42() {
        if (!strset42_id()) {
            print_info();
            strset42_id() = strset_new();
            strset_insert(strset42_id(), "42");
            print_result();
        }
        
        return strset42_id();
    }

}
}
