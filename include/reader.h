#ifndef MAL_READER_H
#define MAL_READER_H

#include <regex>
#include <memory>
#include "values.h"

class Reader
{
public:
    std::string next();
    std::string peek();
    Reader(std::string);
private:
    std::regex_iterator<std::string::const_iterator> tokens;
    std::string input;
};

std::shared_ptr<MalValue> read_str(std::string);
std::shared_ptr<MalValue> read_form(Reader&);
std::shared_ptr<MalValue> read_atom(Reader&);
std::shared_ptr<MalValue> read_list(Reader&);
std::shared_ptr<MalValue> read_vector(Reader&);
std::shared_ptr<MalValue> read_hashmap(Reader&);


#endif /* MAL_READER_H */
