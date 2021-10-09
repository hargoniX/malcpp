#ifndef MAL_VALUES_H
#define MAL_VALUES_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <utility>

enum MalValueKind {
    List,
    Symbol,
    Number,
    Double,
    Boolean,
    Nil,
    String,
    Keyword,
    Vector,
    HashMap
};

class MalValue
{
public:
    virtual std::string to_string() = 0;
    MalValueKind get_kind();
    MalValue(MalValueKind kind) : kind { kind } {}
private:
    MalValueKind kind;
};

class MalList : public MalValue
{
public:
    MalList(std::vector<std::shared_ptr<MalValue>> list) : MalValue(MalValueKind::List), list{ list }{}
    std::string to_string();
private:
    std::vector<std::shared_ptr<MalValue>> list;
};

class MalSymbol : public MalValue
{
public:
    MalSymbol(std::string name) : MalValue(MalValueKind::Symbol), name { name } {}
    std::string to_string();
private:
    std::string name;
};

class MalNumber : public MalValue
{
public:
    MalNumber(long long value) : MalValue(MalValueKind::Number), value{ value } {}
    std::string to_string();
private:
    long long value;
};

class MalDouble : public MalValue {
public:
    MalDouble(double value) : MalValue(MalValueKind::Number), value { value } {}
    std::string to_string();
private:
    long double value;
};

class MalBoolean : public MalValue
{
public:
    MalBoolean (bool value) : MalValue(MalValueKind::Boolean), value { value } {}
    std::string to_string();
private:
    bool value;
};

class MalNil : public MalValue
{
public:
    MalNil() : MalValue(MalValueKind::Nil) {}
    std::string to_string();
};

class MalString : public MalValue
{
public:
    // TODO: Handle unescaping
    MalString (std::string value) : MalValue(MalValueKind::String), value { value } {}
    std::string to_string();
private:
    std::string value;
};

class MalKeyword : public MalValue
{
public:
    MalKeyword(std::string value) : MalValue(MalValueKind::Keyword), value { value } {}
    std::string to_string();
private:
    std::string value;
};


class MalVector : public MalValue
{
public:
    MalVector(std::vector<std::shared_ptr<MalValue>> value) : MalValue(MalValueKind::Vector), list { value } {}
    std::string to_string();
private:
    std::vector<std::shared_ptr<MalValue>> list;
};

class MalHashKey {
public:
    MalHashKey(MalValueKind kind, std::string repr) : kind { kind }, repr { repr } {}
    std::string get_repr() const;
    MalValueKind get_value_kind() const;
    bool operator==(const MalHashKey& other) const;
private:
    std::string repr;
    MalValueKind kind;
};

namespace std
{
    template<> struct hash<MalHashKey>
    {
        std::size_t operator()(MalHashKey const& k) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(k.get_value_kind());
            std::size_t h2 = std::hash<std::string>{}(k.get_repr());
            return h1 ^ (h2 << 1);
        }
    };
}

// TODO: The hashmap should probably not have pointers as values
class MalHashMap : public MalValue
{
public:
    MalHashMap(std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> value) : MalValue(MalValueKind::HashMap), map { value } {}
    std::string to_string();
private:
    std::unordered_map<MalHashKey, std::shared_ptr<MalValue>> map;
};

#endif /* MAL_VALUES_H */
