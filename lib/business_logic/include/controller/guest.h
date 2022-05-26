#ifndef CONTROLLER_GUEST_H
#define CONTROLLER_GUEST_H


#include <iostream>
#include <utility>
#include <vector>
#include "model/post.h"
#include "model/user.h"
#include "repository/post.h"
#include "repository/user.h"


class GuestController
{
public:
    explicit GuestController(IPostRepository *post_repo, IUserRepository *user_repo):
        _post_repo(post_repo), _user_repo(user_repo){};

    UserBL sign_in(const std::string &name, const std::string &surname, const std::string &login,
                   const std::string &password, const std::string &city, const std::string &access);
    bool log_in(const std::string &login, const std::string &password);
    PostBL get_post(int post_id);
    std::vector<PostBL> get_posts(std::vector<int> &post_ids);
    std::vector<PostBL> get_posts();
    std::string get_post_info(int post_id);

protected:
    IPostRepository *_post_repo;
    IUserRepository *_user_repo;
};


#endif  // CONTROLLER_GUEST_H
