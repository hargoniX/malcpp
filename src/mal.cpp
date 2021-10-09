#include <iostream>
#include <string>
#include <memory>

#include "reader.h"
#include "values.h"

std::shared_ptr<MalValue> read(std::string code) {
    return read_str(code);
}

std::shared_ptr<MalValue> eval(std::shared_ptr<MalValue> value) {
    return value;
}

std::string print(std::shared_ptr<MalValue> value) {
    return value->to_string();
}

std::string rep(std::string code) {
    return print(eval(read(code)));
}

int main () {
    while(true) {
        std::cout << "mal> ";
        std::string code{};
        std::getline(std::cin, code);
        if(std::cin.eof()) {
            return 0;
        }

        std::cout << rep(code) << "\n";
    }
}
