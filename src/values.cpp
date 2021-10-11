#include <string>
#include "values.h"
#include "environment.h"

MalValueKind MalValue::get_kind() {
    return kind;
}

std::vector<std::shared_ptr<MalValue>> MalList::to_list() {
    return list;
}

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

long long MalNumber::to_ll() {
    return value;
}

std::string MalNumber::to_string() {
    return std::to_string(value);
}

long double MalDouble::to_ld() {
    return value;
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

std::string MalKeyword::to_string() {
    return value;
}

std::vector<std::shared_ptr<MalValue>> MalVector::to_list() {
    return list;
}

std::string MalVector::to_string() {
    std::string ret = "[";
    for (auto i = list.begin(); i != list.end(); ++i) {
        ret += (*i)->to_string();
        if (i + 1 != list.end()) {
            ret += " ";
        }
    }
    ret += "]";
    return ret;
}

std::string MalHashKey::get_repr() const {
    return repr;
}

MalValueKind MalHashKey::get_value_kind() const {
    return kind;
}

bool MalHashKey::operator==(const MalHashKey& other) const {
    return repr == other.repr && kind == other.kind;
}

std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> MalHashMap::to_hashmap() {
    return map;
}

std::string MalHashMap::to_string() {
    std::string ret = "{ ";
    for(const auto& kv : map) {
        ret += kv.first.get_repr();
        ret += " ";
        ret += kv.second->to_string();
        // TODO: This should be conditional if we are at the last pair ommit it
        ret += " ";
    }

    ret += "}";
    return ret;
}

std::shared_ptr<MalValue> MalFunction::call(std::vector<std::shared_ptr<MalValue>> args, std::shared_ptr<Environment> env) {
    return fun(args, env);
}

std::string MalFunction::to_string() {
    return "#<function>";
}
