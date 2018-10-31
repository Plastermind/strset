#include <iostream>

#include "strset.h"
#include "strsetconst.h"
    
#ifndef NDEBUG 
    const bool debug = true;
#else 
    const bool debug = false;
#endif

namespace jnp1 {
	

namespace {
    static unsigned long strset42_id = 0;

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
} // namespace

unsigned long strset42() {
    if (!strset42_id) {
        print_info();
        strset42_id = strset_new();
        strset_insert(strset42_id, "42");
        print_result();
    }
        
    return strset42_id;
}


} // namespace jnp1
