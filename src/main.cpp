#include <iostream>
#include "database/pg_database.h"
#include "database/config.h"


int main()
{
    PGDatabase db(PGDatabaseParams);
    std::vector<User> users = db.get_users();
    for (auto &user: users)
        std::cout << user.get_login();
    
    return 0;
}
