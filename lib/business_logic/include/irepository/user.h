#ifndef IREPOSITORY_USER_H
#define IREPOSITORY_USER_H


#include "model_bl/user.h"


class IUserRepository
{
public:
    virtual UserBL get_user(int user_id) = 0;
    virtual bool check_user(const std::string &login, const std::string &password) = 0;
    virtual std::vector<UserBL> get_users() = 0;
    virtual UserBL add_user(std::string name, std::string surname, std::string login,
                            std::string password, std::string city, std::string access) = 0;
    virtual UserBL delete_user(int user_id) = 0;
    virtual UserBL update_user(int user_id, std::string name, std::string surname, std::string login,
                               std::string password, std::string city, std::vector<PostBL> posts, bool upd_posts) = 0;
    virtual UserBL update_user(UserBL user, const std::string& name, const std::string& surname, const std::string& login,
                               const std::string& password, const std::string& city, std::vector<PostBL> posts, bool upd_posts) = 0;
};


#endif  // IREPOSITORY_USER_H
