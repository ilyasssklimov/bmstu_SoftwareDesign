#ifndef PG_DATABASE_H
#define PG_DATABASE_H

#include "config.h"
#include "database.h"
#include <pqxx/pqxx>


class PGDatabase: public IDataBase
{
public:
    explicit PGDatabase(const std::string &params): IDataBase(params) {} ;
    std::vector<User> get_users() override;
};

#endif  // PG_DATABASE_H
