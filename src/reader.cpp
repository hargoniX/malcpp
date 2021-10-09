#include <stdexcept>
#include <string>
#include <regex>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <utility>

#include "reader.h"
#include "values.h"

static std::regex token_regex(R"([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))");
static std::regex int_regex("-?[0-9]+$");
static std::regex float_regex("-?[0-9][0-9.]*$");
static std::regex string_regex(R"("(?:\\.|[^\\"])*"?)");

Reader::Reader(std::string input) : input {input} {
    this->tokens = std::sregex_iterator(this->input.begin(), this->input.end(), token_regex);
}

std::string Reader::next() {
    ++tokens;
    return peek();
}

std::string Reader::peek() {
    if (tokens != std::sregex_iterator()) {
        std::smatch match = *tokens;
        return match.str(1);
    } else {
        return "";
    }
}

std::shared_ptr<MalValue> read_str(std::string code) {
    Reader tokenizer = Reader(code);

    std::string token = tokenizer.peek();
    while(token != "" && token.at(0) == ';'){
        token = tokenizer.next();
    }

    if (tokenizer.peek() == "") {
        return std::shared_ptr<MalNil>(new MalNil());
    }

    try {
        return read_form(tokenizer);
    } catch(int error) {
        std::cout << "Parse error\n";
        return std::shared_ptr<MalNil>(new MalNil());
    }
}

std::shared_ptr<MalValue> read_form(Reader& tokenizer) {
    std::string token = tokenizer.peek();
    if (token == "") {
        throw -1;
    } else if (token == "(") {
        return read_list(tokenizer);
    } else if (token == "[") {
        return read_vector(tokenizer);
    } else if (token == "{") {
        return read_hashmap(tokenizer);
    } else {
        return read_atom(tokenizer);
    }
}

std::shared_ptr<MalValue> read_list(Reader& tokenizer) {
    std::vector<std::shared_ptr<MalValue>> values;
    for (;;) {
        std::string token = tokenizer.next();
        if (token == "") {
            throw -1;
        } else if (token == ")") {
            return std::shared_ptr<MalList>(new MalList(values));
        } else {
            values.push_back(read_form(tokenizer));
        }
    }
}

std::shared_ptr<MalValue> read_vector(Reader& tokenizer) {
    std::vector<std::shared_ptr<MalValue>> values;
    for (;;) {
        std::string token = tokenizer.next();
        if (token == "") {
            throw -1;
        } else if (token == "]") {
            return std::shared_ptr<MalVector>(new MalVector(values));
        } else {
            values.push_back(read_form(tokenizer));
        }
    }
}

std::shared_ptr<MalValue> read_hashmap(Reader& tokenizer) {
    std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> values;
    for (;;) {
        std::string token = tokenizer.next();

        if (token == "") {
            throw -1;
        } else if (token == "}") {
            return std::shared_ptr<MalHashMap>(new MalHashMap(values));
        } else {
            std::shared_ptr<MalValue> key = read_form(tokenizer);
            MalValueKind kind = key->get_kind();
            switch(kind) {
                case MalValueKind::Symbol:
                case MalValueKind::Number:
                case MalValueKind::Double:
                case MalValueKind::Boolean:
                case MalValueKind::Nil:
                case MalValueKind::String:
                case MalValueKind::Keyword:
                    {
                        MalHashKey hkey = MalHashKey(kind, key->to_string());
                        std::string token = tokenizer.next();
                        if (token == "") {
                            throw -1;
                        } else if (token == "}") {
                            throw -2;
                        } else {
                            std::shared_ptr<MalValue> value = read_form(tokenizer);
                            values[hkey] = value;
                        }
                        break;
                    }
                default:
                    // Only the above types are supported for now
                    throw -1;
                    break;
            }
        }
        
    }
}

std::shared_ptr<MalValue> read_atom(Reader& tokenizer) {
    std::string token = tokenizer.peek();
    if (token == "true") {
        return std::shared_ptr<MalBoolean>(new MalBoolean(true));
    } else if (token == "false") {
        return std::shared_ptr<MalBoolean>(new MalBoolean(false));
    } else if (token == "nil") {
        return std::shared_ptr<MalNil>(new MalNil());
    } else if (std::regex_match(token, int_regex)) {
        return std::shared_ptr<MalNumber>(new MalNumber(std::stoll(token)));
    } else if (std::regex_match(token, float_regex)) {
        return std::shared_ptr<MalDouble>(new MalDouble(std::stold(token)));
    } else if (std::regex_match(token, string_regex)) {
        return std::shared_ptr<MalString>(new MalString(token.substr(1, token.length() - 2)));
    } else if (token.at(0) == ':') {
        return std::shared_ptr<MalKeyword>(new MalKeyword(token));
    } else {
        return std::shared_ptr<MalSymbol>(new MalSymbol(token));
    }
}
