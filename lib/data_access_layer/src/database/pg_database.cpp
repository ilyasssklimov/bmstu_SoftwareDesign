#include <iostream>
#include "database/pg_database.h"


std::vector<User> PGDatabase::get_users()
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);

    pqxx::result response = worker.exec("SELECT * FROM software.public.user");
    std::vector<User> users;

    for (const auto &user_db : response)
    {
        User user(pqxx::to_string(user_db[1]), pqxx::to_string(user_db[2]),
                  pqxx::to_string(user_db[3]), pqxx::to_string(user_db[4]),
                  pqxx::to_string(user_db[5]),pqxx::to_string(user_db[6]));
        users.push_back(user);
    }

    return users;
}



