#include <iostream>
#include <vector> 
#include <set>
#include <string> 

#include "strsetconst.h"


#ifndef NDEBUG 
    const bool debug = true;
#else 
    const bool debug = false;
#endif

using Strset = std::set<std::string>;
using StrsetsContainer = std::vector<Strset>;
using IdsOccupation = std::vector<bool>;

//StrsetsContainer sc;
//IdsOccupation io;
//unsigned long sn;

//StrsetsContainer strsets_container() {
    ////static StrsetsContainer strsets_container;
    //return sc;
//}
//IdsOccupation ids_occupation() {
    ////static IdsOccupation ids_occupation;
    //return io;
//}

//unsigned long strsets_number() {
    ////static unsigned long strsets_number = 0;
    //return sn;
//}
// AUXILIARY FUNCTIONS

StrsetsContainer& strsets_container() {
    static StrsetsContainer strsets_container;
    return strsets_container;
}
IdsOccupation& ids_occupation() {
    static IdsOccupation ids_occupation;
    return ids_occupation;
}

unsigned long& strsets_number() {
    static unsigned long strsets_number = 0;
    return strsets_number;
}

//void print_info(std::string command_name 

bool strset_exist(unsigned long id) {
    return strsets_number() >= id && ids_occupation()[id];
}
namespace jnp1 {
    extern "C" {

// STRSET FUNCTIONS

//Tworzy nowy zbiór i zwraca jego identyfikator.
unsigned long strset_new() {
    ++strsets_number();
    strsets_container().resize(strsets_number() + 1);
    ids_occupation().resize(strsets_number() + 1);
    
    ids_occupation().back() = 1;
    
    return strsets_number();
}
    
//Jeżeli istnieje zbiór o identyfikatorze id, usuwa go, a w przeciwnym
//przypadku nie robi nic.
void strset_delete(unsigned long id) {
    if (strset42() == id) {
        return;
    }
    if (strset_exist(id)) {
        ids_occupation()[id] = false;
    }
    else {
        
    }
}

//Jeżeli istnieje zbiór o identyfikatorze id, zwraca liczbę jego elementów,
//a w przeciwnym przypadku zwraca 0.      
size_t strset_size(unsigned long id) {
    if (strset_exist(id)) {
        return strsets_container()[id].size();
    }
    else {
        return 0;
    }
}

//Jeżeli istnieje zbiór o identyfikatorze id i element value nie należy do
//tego zbioru, to dodaje element do zbioru, a w przeciwnym przypadku nie
//robi nic.
void strset_insert(unsigned long id, const char* value) {
    //std::cout << __FUNCTION__ << std::endl;
    if (value == nullptr) {
        return;
    } 
    if (strset42() == id) {
        if (strsets_container()[id].empty()) {
            strsets_container()[id].insert(std::string(value));
        }
        else {
            
        }
        
        return;
    }
    if (strset_exist(id)) {
        strsets_container()[id].insert(std::string(value));
    } 
    else {
        
    }
}

//Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
//zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie robi nic.
void strset_remove(unsigned long id, const char* value) {
    if (value == nullptr) {
        return;
    }
    if (strset42() == id) {
        return;
    }
    if (strset_exist(id)) {
        strsets_container()[id].erase(std::string(value));
    } 
    else {
        
    }
}


//Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
//zbioru, to zwraca 1, a w przeciwnym przypadku 0.
int strset_test(unsigned long id, const char* value) {
    if (value == nullptr) {
        return 0;
    }
    if (strset_exist(id)) {
        return strsets_container()[id].count(std::string(value));
    }
    else {
        return 0;
    }
}

//Jeżeli istnieje zbiór o identyfikatorze id, usuwa wszystkie jego elementy,
//a w przeciwnym przypadku nie robi nic.
void strset_clear(unsigned long id) {
    if (strset42() == id) {
        return;
    }
    if (strset_exist(id)) {
        strsets_container()[id].clear();
    }
    else {
        
    }
}

//Porównuje zbiory o identyfikatorach id1 i id2. Niech sorted(id) oznacza
//posortowany leksykograficznie zbiór o identyfikatorze id. Takie ciągi już
//porównujemy naturalnie: pierwsze miejsce, na którym się różnią, decyduje
//o relacji większości. Jeśli jeden ciąg jest prefiksem drugiego, to ten
//będący prefiks jest mniejszy. Funkcja strset_comp(id1, id2) powinna zwrócić
//-1, gdy sorted(id1) < sorted(id2),
//0, gdy sorted(id1) = sorted(id2),
//1, gdy sorted(id1) > sorted(id2).
//Jeżeli zbiór o którymś z identyfikatorów nie istnieje, to jest traktowany
//jako równy zbiorowi pustemu.
int strset_comp(unsigned long id1, unsigned long id2) {
    Strset strset1, strset2;
    
    if (strset_exist(id1)) strset1 = strsets_container()[id1];
    if (strset_exist(id2)) strset2 = strsets_container()[id2];
    
    if (strset1 < strset2) return -1;
    else if (strset1 > strset2) return 1;
    else return 0;
}

}
}
