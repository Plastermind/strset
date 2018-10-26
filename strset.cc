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
using Strset_id = unsigned long;

// AUXILIARY FUNCTIONS

StrsetsContainer& strsets_container() {
    static StrsetsContainer strsets_container;
    return strsets_container;
}
IdsOccupation& ids_occupation() {
    static IdsOccupation ids_occupation;
    return ids_occupation;
}

void initialize_stream() {
    std::ios_base::Init();
}

unsigned long& strsets_number() {
    static unsigned long strsets_number;
    return strsets_number;
}

bool strset_exist(unsigned long id) {
    return strsets_number() >= id && ids_occupation()[id];
}

void print_info(std::string name, Strset_id id1, Strset_id id2, const char* value) {
    if (!debug) return;

    std::string info = "strset_" + name + "(";
    
    if (name == "delete" || name == "size" || name == "clear") {
        info += std::to_string(id1);  
    }
    else if (name == "insert" || name == "remove" || name == "test") {
        info += std::to_string(id1) + ", " + 
            (value == nullptr ? "NULL" : "\"" + std::string(value) + "\"");        
    }
    else if (name == "comp") {
        info += std::to_string(id1) + ", " + std::to_string(id2);
    }
    
    info += ")";
    
    initialize_stream();
    std::cerr << info << std::endl;
}  

void print_result(std::string name, Strset_id id1, Strset_id id2, const char* value, int result) {
    if (!debug) return;
    
    std::string set1_name = 
        (id1 && id1 == jnp1::strset42() ? "the 42 Set" : "set " + std::to_string(id1));
    std::string set2_name = 
        (id2 && id2 == jnp1::strset42() ? "the 42 Set" : "set " + std::to_string(id2));
    std::string info = "strset_" + name + ": ";
    
    if (name == "new") {
        info += "set " + std::to_string(result) + " created";
    }
    else if (name == "delete") {
        info += "set " + std::to_string(result) + " deleted";
    }
    else if (name == "insert") {
        info += "element \"" + std::string(value) + "\" ";
        info += (result ? "inserted" : "was already present");
    }
    else if (name == "remove") {
        info += "element " + std::string(value) + " ";
        info += (result ? "removed" : "was not present");        
    }
    else if (name == "size") {
        info += set1_name + " contains ";
        info += std::to_string(result) + " element(s)";
    }
    else if (name == "test") {
        info += set1_name + " ";
        info += (result ? "contains" : "does not contain");
        info += " the element \"" + std::string(value) + "\"";
    }
    else if (name == "clear") {
        info += set1_name + " cleared";
    }
    else if (name == "comp") {
        info += "result of comparing " + set1_name + " to " + set2_name
             + " is " + std::to_string(result);
    }
    
    initialize_stream();
    std::cerr << info << std::endl;
}


bool check_id(std::string command_name, unsigned long id) {
    bool result = strset_exist(id);
    
    if (!result) {
        initialize_stream();
        std::string error = "strset_" + command_name + ": set" + std::to_string(id)
                            + " does not exist";
        std::cerr << error << std::endl;
    }
    
    return result;
}

bool check_value(std::string command_name, const char *value) {
    bool result = value != nullptr;
    
    if (!result) {
        initialize_stream();
        std::string error = "strset_" + command_name + ": invalid value (NULL)";
        std::cerr << error << std::endl;
    }
    
    return result;    
}

bool check_set42(std::string command_name, unsigned long id) {
    if (id == jnp1::strset42()) {
        if (debug) {
            std::string error = "strset_" + command_name + ": attempt to ";
            if (command_name == "insert") {
                error += "insert into the 42 set";
            }
            else if (command_name == "remove") {
                error += "remove element from the 42 set";
            }
            else if (command_name == "clear") {
                error += "clear the 42 set";
            }
            else if (command_name == "delete") {
                error += "delete the 42 set";
            }
            initialize_stream();
            std::cerr << error << std::endl;
        }
        
        return true;
    }
    
    return false;
}

namespace jnp1 {
    extern "C" {

    // STRSET FUNCTIONS

    //Tworzy nowy zbiór i zwraca jego identyfikator.
    unsigned long strset_new() {
        print_info("new", 0, 0, nullptr);
        ++strsets_number();
        strsets_container().resize(strsets_number() + 1);
        ids_occupation().resize(strsets_number() + 1);
        
        ids_occupation().back() = 1;
        
        print_result("new", 0, 0, nullptr, 1);
        return strsets_number();
        //return 1;
    }
        
    //Jeżeli istnieje zbiór o identyfikatorze id, usuwa go, a w przeciwnym
    //przypadku nie robi nic.
    void strset_delete(unsigned long id) {
        print_info("delete", id, 0, nullptr);
        
        bool is_query_correct = check_id("delete", id) && !check_set42("delete", id);
         
        if (is_query_correct) {
            ids_occupation()[id] = false;
            print_result("delete", id, 0, nullptr, 1);
        }
    }

    //Jeżeli istnieje zbiór o identyfikatorze id, zwraca liczbę jego elementów,
    //a w przeciwnym przypadku zwraca 0.      
    size_t strset_size(unsigned long id) {
        print_info("size", id, 0, nullptr);
        
        int result;
        
        if (strset_exist(id)) result = strsets_container()[id].size();
        else result = 0;
        
        print_result("size", id, 0, nullptr, result);
        
        return result;
    }

    //Jeżeli istnieje zbiór o identyfikatorze id i element value nie należy do
    //tego zbioru, to dodaje element do zbioru, a w przeciwnym przypadku nie
    //robi nic.
    void strset_insert(unsigned long id, const char* value) {
        print_info("insert", id, 0, value);
        bool is_query_correct = check_value("insert", value) 
                                && check_id("insert", id);
        if (!is_query_correct) return;
        
        if (strsets_container()[id].empty()) {
            strsets_container()[id].insert(std::string(value));
        }
        else {
            if (!check_set42("insert", id)) {
                strsets_container()[id].insert(std::string(value));
            } 
            else return;
        }
        
        print_result("insert", id, 0, value, 1);
    }

    //Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
    //zbioru, to zwraca 1, a w przeciwnym przypadku 0.
    int strset_test(unsigned long id, const char* value) {
        print_info("test", id, 0, value);
        
        bool is_query_correct = check_id("test", id) &&
                                check_value("test", value);
        if (!is_query_correct) return 0;
        
        int result = strsets_container()[id].count(std::string(value));
        print_result("test", id, 0, value, result);
        
        return result;
    }

    //Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
    //zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie robi nic.
    void strset_remove(unsigned long id, const char* value) {
        print_info("remove", id, 0, value);
        
        bool is_query_correct = check_value("remove", value) &&
                                check_id("remove", id) && 
                                !check_set42("remove", id);
                                
        if (!is_query_correct) return;
        
        bool result = false;
        
        if (strset_test(id, value)) {
            result = true;
            strsets_container()[id].erase(std::string(value));
        } 
        
        print_result("remove", id, 0, value, result);
    }

    //Jeżeli istnieje zbiór o identyfikatorze id, usuwa wszystkie jego elementy,
    //a w przeciwnym przypadku nie robi nic.
    void strset_clear(unsigned long id) {
        print_info("clear", id, 0, nullptr);
        
        bool is_query_correct = check_id("remove", id) && 
                                !check_set42("remove", id);
        if (!is_query_correct) return;
        
        strsets_container()[id].clear();
        
        print_result("clear", id, 0, nullptr, 1);
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
        print_info("comp", id1, id2, nullptr);
        Strset strset1, strset2;
        
        if (strset_exist(id1)) strset1 = strsets_container()[id1];
        if (strset_exist(id2)) strset2 = strsets_container()[id2];
        
        int result = 0;
        if (strset1 < strset2) result = -1;
        else if (strset1 > strset2) result = 1;
        
        print_result("comp", id1, id2, nullptr, result);
        return result;
    }

}
}
