#include <memory>

#include "environment.h"
#include "values.h"
#include "operations.h"

Environment::Environment() {
    this->env["+"] = std::shared_ptr<MalFunction>(new MalFunction(mal_addition));
    this->env["-"] = std::shared_ptr<MalFunction>(new MalFunction(mal_subtraction));
    this->env["*"] = std::shared_ptr<MalFunction>(new MalFunction(mal_multiplication));
    this->env["/"] = std::shared_ptr<MalFunction>(new MalFunction(mal_division));
}

std::shared_ptr<MalValue> Environment::get_symbol(std::string symbol) {
    std::shared_ptr<MalValue> val = env[symbol];
    if (val == nullptr) {
        throw -1;
    }
    return val;
}
