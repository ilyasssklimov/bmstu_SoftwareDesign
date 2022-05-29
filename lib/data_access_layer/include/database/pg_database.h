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
    User get_user(int user_id) override;
    User get_user(const std::string &login, const std::string &password) override;
    User add_user(std::string name, std::string surname, std::string login,
                  std::string password, std::string city, std::string access) override;
    User delete_user(int user_id) override;
    User update_user(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                     const std::string& password, const std::string& city, const std::vector<int>& posts) override;
    User update_user(User user, const std::string &name, std::string surname, std::string login,
                     const std::string &password, const std::string &city, const std::vector<int> &posts) override;

    std::vector<Post> get_posts() override;
    Post get_post(int post_id) override;
    std::vector<Post> get_posts(const std::string& date, const std::string& name,
                                const std::string& city, int author) override;
    Post add_post(std::string name, int author_id, std::string information, std::string city,
                          std::string organizer, std::string data) override;
    Post delete_post(int post_id) override;
    Post update_post(int post_id, std::string name, std::string information,
                     std::string city, std::string data) override;

    Comment get_comment(int comment_id) override;
    Comment add_comment(std::string data, std::string text, int author_id, int post_id) override;
    Comment delete_comment(int comment_id) override;
    Comment update_comment(int comment_id, std::string date, std::string text) override;
};

#endif  // PG_DATABASE_H
