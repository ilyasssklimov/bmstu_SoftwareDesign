#ifndef CONTROLLER_AUTHOR_H
#define CONTROLLER_AUTHOR_H


#include "client.h"


class AuthorController: public ClientController
{
public:
    explicit AuthorController(int id, IPostRepository *post_repo, ICommentRepository *comment_repo, IUserRepository *user_repo):
        ClientController(id, post_repo, comment_repo, user_repo) {};

    PostBL create_post(const std::string &name, const std::string &info, const std::string &city,
                       const std::string &organizer,  const std::string &data);
};


#endif  // CONTROLLER_AUTHOR_H
