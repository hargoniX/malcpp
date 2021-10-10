#ifndef MAL_EVAL_H
#define MAL_EVAL_H

#include <memory>
#include "values.h"
#include "environment.h"

std::shared_ptr<MalValue> eval(std::shared_ptr<MalValue>, Environment&);
std::shared_ptr<MalValue> eval_ast(std::shared_ptr<MalValue>, Environment&);

#endif /* MAL_EVAL_H */
