#ifndef MAL_VALUES_H
#define MAL_VALUES_H

#include <vector>
#include <string>
#include <memory>

class MalValue
{
public:
    virtual std::string to_string() = 0;
};

class MalList : public MalValue
{
public:
    MalList(std::vector<std::shared_ptr<MalValue>> list) : list{ list } {}
    std::string to_string();
private:
    std::vector<std::shared_ptr<MalValue>> list;
};

class MalSymbol : public MalValue
{
public:
    MalSymbol(std::string name) : name { name } {}
    std::string to_string();
private:
    std::string name;
};

class MalNumber : public MalValue
{
public:
    MalNumber(long long value) : value{ value } {}
    std::string to_string();
private:
    long long value;
};

class MalDouble : public MalValue {
public:
    MalDouble(double value) : value { value } {}
    std::string to_string();
private:
    long double value;
};

class MalBoolean : public MalValue
{
public:
    MalBoolean (bool value) : value { value } {}
    std::string to_string();
private:
    bool value;
};

class MalNil : public MalValue
{
    std::string to_string();
};

class MalString : public MalValue
{
public:
    // TODO: Handle unescaping
    MalString (std::string value) : value { value } {}
    std::string to_string();
private:
    std::string value;
};

#endif /* MAL_VALUES_H */
