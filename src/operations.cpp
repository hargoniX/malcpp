#include <memory>
#include <vector>
#include "values.h"
#include "operations.h"
#include "environment.h"

// TOOD: Auto type conversion can be done here for double and int
std::shared_ptr<MalValue> mal_addition(std::vector<std::shared_ptr<MalValue>> args, std::shared_ptr<Environment> env) {
    if(args.size() != 2) {
        throw -1;
    }

    std::shared_ptr<MalValue> lhs = args[0];
    if (lhs->get_kind() == MalValueKind::Number) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Number) {
            throw -1;
        }

        long long result = lhs->to_ll() + rhs->to_ll();
        return std::shared_ptr<MalValue>(new MalNumber(result));
    } else if (lhs->get_kind() == MalValueKind::Double) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Double) {
            throw -1;
        }
        long double result = lhs->to_ld() + rhs->to_ld();
        return std::shared_ptr<MalValue>(new MalDouble(result));
    } else {
        throw -1;
    }
}

std::shared_ptr<MalValue> mal_subtraction(std::vector<std::shared_ptr<MalValue>> args, std::shared_ptr<Environment> env) {
    if(args.size() != 2) {
        throw -1;
    }

    std::shared_ptr<MalValue> lhs = args[0];
    if (lhs->get_kind() == MalValueKind::Number) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Number) {
            throw -1;
        }

        long long result = lhs->to_ll() - rhs->to_ll();
        return std::shared_ptr<MalValue>(new MalNumber(result));
    } else if (lhs->get_kind() == MalValueKind::Double) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Double) {
            throw -1;
        }
        long double result = lhs->to_ld() - rhs->to_ld();
        return std::shared_ptr<MalValue>(new MalDouble(result));
    } else {
        throw -1;
    }
}

std::shared_ptr<MalValue> mal_multiplication(std::vector<std::shared_ptr<MalValue>> args, std::shared_ptr<Environment> env) {
    if(args.size() != 2) {
        throw -1;
    }

    std::shared_ptr<MalValue> lhs = args[0];
    if (lhs->get_kind() == MalValueKind::Number) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Number) {
            throw -1;
        }

        long long result = lhs->to_ll() * rhs->to_ll();
        return std::shared_ptr<MalValue>(new MalNumber(result));
    } else if (lhs->get_kind() == MalValueKind::Double) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Double) {
            throw -1;
        }
        long double result = lhs->to_ld() * rhs->to_ld();
        return std::shared_ptr<MalValue>(new MalDouble(result));
    } else {
        throw -1;
    }
}

std::shared_ptr<MalValue> mal_division(std::vector<std::shared_ptr<MalValue>> args, std::shared_ptr<Environment> env) {
    if(args.size() != 2) {
        throw -1;
    }

    std::shared_ptr<MalValue> lhs = args[0];
    if (lhs->get_kind() == MalValueKind::Number) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Number) {
            throw -1;
        }

        long long result = lhs->to_ll() / rhs->to_ll();
        return std::shared_ptr<MalValue>(new MalNumber(result));
    } else if (lhs->get_kind() == MalValueKind::Double) {
        std::shared_ptr<MalValue> rhs = args[1];
        if (rhs->get_kind() != MalValueKind::Double) {
            throw -1;
        }
        long double result = lhs->to_ld() / rhs->to_ld();
        return std::shared_ptr<MalValue>(new MalDouble(result));
    } else {
        throw -1;
    }
}
