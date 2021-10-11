#ifndef MAL_OPERATIONS_H
#define MAL_OPERATIONS_H

#include <memory>
#include <vector>
#include "values.h"
#include "environment.h"

std::shared_ptr<MalValue> mal_addition(std::vector<std::shared_ptr<MalValue>>, std::shared_ptr<Environment>);
std::shared_ptr<MalValue> mal_subtraction(std::vector<std::shared_ptr<MalValue>>, std::shared_ptr<Environment>);
std::shared_ptr<MalValue> mal_multiplication(std::vector<std::shared_ptr<MalValue>>, std::shared_ptr<Environment>);
std::shared_ptr<MalValue> mal_division(std::vector<std::shared_ptr<MalValue>>, std::shared_ptr<Environment>);

#endif /* MAL_OPERATIONS_H */
