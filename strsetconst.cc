#include <iostream>
#include <vector> 
#include <set>

#include "strset.h"
    
#ifndef NDEBUG 
    const bool debug = true;
#else 
    const bool debug = false;
#endif

unsigned long& strset42_id() {
    static unsigned long strset42_id = 0;
    return strset42_id;
}

// AUXILIARY FUNCTIONS

// STRSET FUNCTIONS

//Zwraca identyfikator zbioru, którego nie można modyfikować i który zawiera
//jeden element: napis "42". Zbiór jest tworzony przy pierwszym wywołaniu tej
//funkcji i wtedy zostaje ustalony jego numer.
namespace jnp1 {
extern "C" {
unsigned long strset42() {
    if (strset42_id() == 0) {
        strset42_id() = strset_new();
        strset_insert(strset42_id(), "42");
    }
    return strset42_id();
}

}
}
