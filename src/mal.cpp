#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "reader.h"
#include "values.h"
#include "environment.h"
#include "eval.h"

std::shared_ptr<MalValue> read(std::string code) {
    return read_str(code);
}

std::string print(std::shared_ptr<MalValue> value) {
    return value->to_string();
}

std::string rep(std::string code, Environment& env) {
    return print(eval(read(code), env));
}

int main () {
    Environment env = Environment();
    while(true) {
        std::cout << "mal> ";
        std::string code{};
        std::getline(std::cin, code);
        if(std::cin.eof()) {
            return 0;
        }

        std::cout << rep(code, env) << "\n";
    }
}
