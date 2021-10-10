#include <memory>
#include <unordered_map>
#include <vector>

#include "environment.h"
#include "values.h"
#include "eval.h"

std::shared_ptr<MalValue> eval(std::shared_ptr<MalValue> value, Environment& env) {
    MalValueKind kind = value->get_kind();
    switch(kind) {
        case MalValueKind::List:
            {
                std::vector<std::shared_ptr<MalValue>> list = value->to_list();
                if (list.size() == 0) {
                    return value;
                } else {
                    std::shared_ptr<MalValue> new_val = eval_ast(value, env);
                    std::vector<std::shared_ptr<MalValue>> list = new_val->to_list();
                    if (list[0]->get_kind() != MalValueKind::Symbol) {
                        throw -1;
                    }

                    // XXX: Symbol string hack
                    std::shared_ptr<MalValue> func = env.get_symbol(list[0]->to_string());
                    if (func->get_kind() != MalValueKind::Function) {
                        throw -1;
                    }
                    // XXX: Ideally we dont want to copy stuff acrross like this but instead
                    // use iterators as arguments for MalFunctions.
                    return func->call(std::vector<std::shared_ptr<MalValue>>(list.begin() + 1, list.end()));
                }
                
            }
        case MalValueKind::Vector:
            {
                std::vector<std::shared_ptr<MalValue>> list = value->to_list();
                if (list.size() == 0) {
                    return value;
                } else {
                    return eval_ast(value, env);
                }
                
            }
        case MalValueKind::HashMap:
            {
                std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> map = value->to_hashmap();
                if (map.size() == 0) {
                    return value;
                } else {
                    return eval_ast(value, env);
                }
            }
        default: 
            return value;
    }
}

std::shared_ptr<MalValue> eval_ast(std::shared_ptr<MalValue> ast, Environment& env) {
    MalValueKind kind = ast->get_kind();
    switch(kind) {
        case MalValueKind::Symbol:
            // XXX: Hack, there should be a to_string() and a to_repr() function
            return env.get_symbol(ast->to_string());
        case MalValueKind::List:
            {
                std::vector<std::shared_ptr<MalValue>> list = ast->to_list();
                std::vector<std::shared_ptr<MalValue>> new_list;
                for (auto i = list.begin(); i != list.end(); ++i) {
                    new_list.push_back(eval(*i, env));
                }
                return std::shared_ptr<MalValue>(new MalList(new_list));
            }
        case MalValueKind::Vector:
            {
                std::vector<std::shared_ptr<MalValue>> list = ast->to_list();
                std::vector<std::shared_ptr<MalValue>> new_list;
                for (auto i = list.begin(); i != list.end(); ++i) {
                    new_list.push_back(eval(*i, env));
                }
                return std::shared_ptr<MalValue>(new MalVector(new_list));
            }
        case MalValueKind::HashMap:
            {
                std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> map = ast->to_hashmap();
                std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> new_map;
                for (const auto& kv : map) {
                    new_map[kv.first] =  eval(kv.second, env);
                }
                return std::shared_ptr<MalValue>(new MalHashMap(new_map));
            }
        default:
            return ast;
    }
}
