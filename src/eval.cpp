#include <memory>
#include <unordered_map>
#include <vector>

#include "environment.h"
#include "values.h"
#include "eval.h"

std::shared_ptr<MalValue> eval(std::shared_ptr<MalValue> value, std::shared_ptr<Environment> env) {
    MalValueKind kind = value->get_kind();
    switch(kind) {
        case MalValueKind::List:
            {
                std::vector<std::shared_ptr<MalValue>> list = value->to_list();
                if (list.size() == 0) {
                    return value;
                } else {
                    if (list[0]->get_kind() != MalValueKind::Symbol) {
                        throw -1;
                    }

                    std::string symbol_name = list[0]->to_string();
                    if (symbol_name ==  "def!") {
                        if (list.size() != 3 || list[1]->get_kind() != MalValueKind::Symbol) {
                            throw -1;
                        }
                        // XXX: Symbol string hack
                        env->set_symbol(list[1]->to_string(), eval(list[2], env));
                        return env->get_symbol(list[1]->to_string());
                    } else if (symbol_name == "let*") {
                        if (list.size() != 3 || list[1]->get_kind() != MalValueKind::List) {
                            throw -1;
                        }

                        std::vector<std::shared_ptr<MalValue>> args = list[1]->to_list();
                        if (args.size() % 2 != 0) {
                            throw -1;
                        }

                        std::shared_ptr<Environment> new_env = std::shared_ptr<Environment>(new Environment(env));
                        for(int i = 0; i < args.size(); i+=2) {
                            std::shared_ptr<MalValue> sym = args[i];
                            std::shared_ptr<MalValue> val = args[i+1];
                            if (sym->get_kind() != MalValueKind::Symbol) {
                                throw -1;
                            }
                            new_env->set_symbol(sym->to_string(), eval(val, new_env));
                        }
                        return eval(list[2], new_env);
                    } else {
                        // This should still be a list
                        std::shared_ptr<MalValue> new_val = eval_ast(value, env);
                        std::vector<std::shared_ptr<MalValue>> evaled_list = new_val->to_list();

                        // The first element of the eval_ast'ed should be a function now
                        std::shared_ptr<MalValue> func = evaled_list[0];
                        if (func->get_kind() != MalValueKind::Function) {
                            throw -1;
                        }
                        return func->call(std::vector<std::shared_ptr<MalValue>>(evaled_list.begin() + 1, evaled_list.end()), env);
                    }
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
            return eval_ast(value, env);
    }
}

std::shared_ptr<MalValue> eval_ast(std::shared_ptr<MalValue> ast, std::shared_ptr<Environment> env) {
    MalValueKind kind = ast->get_kind();
    switch(kind) {
        case MalValueKind::Symbol:
            // XXX: Hack, there should be a to_string() and a to_repr() function
            return env->get_symbol(ast->to_string());
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
