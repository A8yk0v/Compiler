#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
        Token(std::string _type, std::string _name) : type(_type), name(_name) {}

        ~Token() {}

        std::string type;
        std::string name;
};

#endif // TOKEN_H
