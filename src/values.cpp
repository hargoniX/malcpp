#include <string>
#include "values.h"

std::string MalList::to_string() {
    std::string ret = "(";
    for (auto i = list.begin(); i != list.end(); ++i) {
        ret += (*i)->to_string();
        if (i + 1 != list.end()) {
            ret += " ";
        }
    }
    ret += ")";
    return ret;
}


std::string MalSymbol::to_string() {
    return name;
}

std::string MalNumber::to_string() {
    return std::to_string(value);
}

std::string MalDouble::to_string() {
    return std::to_string(value);
}

std::string MalBoolean::to_string() {
    if (value) {
        return "true";
    } else {
        return "false";
    }
}

std::string MalNil::to_string() {
    return "nil";
}

// TODO: Deal with escaping
std::string MalString::to_string() {
    return "\"" + value + "\"";
}
