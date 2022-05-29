#ifndef REPOSITORY_USER_H
#define REPOSITORY_USER_H


#include "database/database.h"
#include "irepository/user.h"


class UserRepository: public IUserRepository
{
public:
    explicit UserRepository(IDataBase *db): _db(db) {};
    UserBL get_user(int user_id) override;
    int get_user_id(UserBL user) override;
    bool check_user(const std::string &login, const std::string &password) override;
    std::vector<UserBL> get_users() override;
    UserBL add_user(std::string name, std::string surname, std::string login,
                    std::string password, std::string city, std::string access) override;
    UserBL delete_user(int user_id) override;
    UserBL update_user(int user_id, std::string name, std::string surname, std::string login,
                       std::string password, std::string city, std::vector<PostBL> posts, bool upd_posts) override;
    UserBL update_user(UserBL user, const std::string& name, const std::string& surname, const std::string& login,
                       const std::string& password, const std::string& city, std::vector<PostBL> posts, bool upd_posts) override;

private:
    IDataBase *_db;
    std::vector<PostBL> get_posts_bl(const std::vector<int> &posts_ids);
    std::vector<int> get_posts_ids(const std::vector<PostBL> &posts_bl);
    UserBL user_to_user_bl(User user);
};


#endif  // REPOSITORY_USER_H
