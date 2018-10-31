#include <iostream>
#include <vector>
#include <set>
#include <string>

#include "strsetconst.h"
#include "strset.h"

#ifndef NDEBUG
    const bool debug = true;
#else
    const bool debug = false;
#endif

namespace jnp1 {


using Strset = std::set<std::string>;
using StrsetsContainer = std::vector<Strset>;
using IdsOccupation = std::vector<bool>;
using Strset_id = unsigned long;
using Command_name = std::string;
using Value = const char*;
using Command_data = std::pair<std::pair<Command_name, Strset_id>,
                std::pair<Strset_id, Value>>;

namespace {
    unsigned long strsets_number;

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

    bool strset_exist(unsigned long id) {
        return strsets_number >= id && ids_occupation()[id];
    }

    void print_info(Command_data data) {
        if (!debug) return;

        auto name = data.first.first;
        auto id1 = data.first.second;
        auto id2 = data.second.first;
        auto value = data.second.second;

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

    void print_result(Command_data command_data, int result) {
        if (!debug) return;

        auto name = command_data.first.first;
        auto id1 = command_data.first.second;
        auto id2 = command_data.second.first;
        auto value = command_data.second.second;

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

    bool check_id(Command_data command_data) {
        auto command_name = command_data.first.first;
        auto id = command_data.first.second;

        bool result = strset_exist(id);

        if (!result) {
            initialize_stream();
            std::string error = "strset_" + command_name + ": set " + std::to_string(id)
                                + " does not exist";
            std::cerr << error << std::endl;
        }

        return result;
    }

    bool check_value(Command_data command_data) {
        std::string command_name = command_data.first.first;
        const char* value = command_data.second.second;

        bool result = value != nullptr;

        if (!result) {
            initialize_stream();
            std::string error = "strset_" + command_name + ": invalid value (NULL)";
            std::cerr << error << std::endl;
        }

        return result;
    }

    bool check_set42(Command_data command_data) {
        auto command_name = command_data.first.first;
        auto id = command_data.first.second;

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
} // namespace

unsigned long strset_new() {
    Command_data data = {{"new", 0}, {0, nullptr}};
    print_info(data);

    ++strsets_number;
    strsets_container().resize(strsets_number + 1);
    ids_occupation().resize(strsets_number + 1);

    ids_occupation().back() = 1;

    print_result(data, 1);
    return strsets_number;
}

void strset_delete(unsigned long id) {
    Command_data data = {{"delete", id}, {0, nullptr}};
    print_info(data);

    bool is_query_correct = check_id(data) && !check_set42(data);

    if (is_query_correct) {
        ids_occupation()[id] = false;
        print_result(data, 1);
    }
}

size_t strset_size(unsigned long id) {
    Command_data data = {{"size", id}, {0, nullptr}};
    print_info(data);

    int result = 0;
    if (strset_exist(id)) result = strsets_container()[id].size();

    print_result(data, result);

    return result;
}

void strset_insert(unsigned long id, const char* value) {
    Command_data data = {{"insert", id}, {0, value}};
    print_info(data);

    bool is_query_correct = check_value(data) && check_id(data);
    if (!is_query_correct) return;

    if (strsets_container()[id].empty()) {
        strsets_container()[id].insert(std::string(value));
    }
    else {
        if (!check_set42(data)) {
            strsets_container()[id].insert(std::string(value));
        }
        else return;
    }

    print_result(data, 1);
}

int strset_test(unsigned long id, const char* value) {
    Command_data data = {{"test", id}, {0, value}};
    print_info(data);

    bool is_query_correct = check_id(data) && check_value(data);
    if (!is_query_correct) return 0;

    int result = strsets_container()[id].count(std::string(value));
    print_result(data, result);

    return result;
}

void strset_remove(unsigned long id, const char* value) {
    Command_data data = {{"remove", id}, {0, value}};
    print_info(data);

    bool is_query_correct = check_value(data) &&
                            check_id(data) &&
                            !check_set42(data);

    if (!is_query_correct) return;

    bool result = false;

    if (strset_test(id, value)) {
        result = true;
        strsets_container()[id].erase(std::string(value));
    }

    print_result(data, result);
}

void strset_clear(unsigned long id) {
    Command_data data = {{"clear", id}, {0, nullptr}};
    print_info(data);

    bool is_query_correct = check_id(data) && !check_set42(data);
    if (!is_query_correct) return;

    strsets_container()[id].clear();

    print_result(data, 1);
}

int strset_comp(unsigned long id1, unsigned long id2) {
    Command_data data = {{"comp", id1}, {id2, nullptr}};
    print_info(data);

    Strset strset1, strset2;

    if (strset_exist(id1)) strset1 = strsets_container()[id1];
    if (strset_exist(id2)) strset2 = strsets_container()[id2];

    int result = 0;
    if (strset1 < strset2) result = -1;
    else if (strset1 > strset2) result = 1;

    print_result(data, result);
    check_id(data);
    std::swap(data.first.second, data.second.first);
    check_id(data);

    return result;
}


} // namespace
