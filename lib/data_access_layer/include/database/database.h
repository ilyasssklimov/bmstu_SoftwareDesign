#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <utility>
#include <vector>
#include "model_dal//user.h"


class IDataBase
{
public:
    virtual std::vector<User> get_users() = 0;

protected:
    explicit IDataBase(std::string params): _params(std::move(params)) {} ;
    std::string _params;
};


#endif  // DATABASE_H
