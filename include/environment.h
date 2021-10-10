#ifndef MAL_ENVIRONMENT_H
#define MAL_ENVIRONMENT_H

#include "values.h"
#include <memory>
#include <unordered_map>

class Environment
{
public:
    Environment();
    std::shared_ptr<MalValue> get_symbol(std::string);
private:
    std::unordered_map<std::string, std::shared_ptr<MalValue>> env;
};

#endif /* MAL_ENVIRONMENT_H */
