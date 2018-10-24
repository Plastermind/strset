#include "strsetconst.h"
#include <iostream> 
namespace {
    unsigned long id = ::jnp1::strset42();
}

int main() {
    volatile unsigned long access = id;
    return (int)access;
}
