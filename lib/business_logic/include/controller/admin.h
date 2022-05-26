#ifndef CONTROLLER_ADMIN_H
#define CONTROLLER_ADMIN_H


#include "client.h"


class AdminController: public ClientController
{
public:
    explicit AdminController(int id, IPostRepository *post_repo, ICommentRepository *comment_repo, IUserRepository *user_repo):
                             ClientController(id, post_repo, comment_repo, user_repo) {};

    PostBL submit_post(PostBL post);
    UserBL delete_user(int user_id);
};


#endif  // CONTROLLER_ADMIN_H
