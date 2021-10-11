#ifndef MAL_ENVIRONMENT_H
#define MAL_ENVIRONMENT_H

#include "values.h"
#include <memory>
#include <unordered_map>

class Environment
{
public:
    Environment();
    Environment(std::shared_ptr<Environment> upper);
    std::shared_ptr<MalValue> get_symbol(std::string);
    void set_symbol(std::string, std::shared_ptr<MalValue>);
private:
    std::unordered_map<std::string, std::shared_ptr<MalValue>> env;
    // XXX: Maybe owned ptr?
    std::shared_ptr<Environment> upper;
};

#endif /* MAL_ENVIRONMENT_H */
