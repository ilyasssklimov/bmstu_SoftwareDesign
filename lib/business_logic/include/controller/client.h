#ifndef CONTROLLER_CLIENT_H
#define CONTROLLER_CLIENT_H


#include "guest.h"
#include "repository/comment.h"
#include "repository/user.h"


class ClientController: public GuestController
{
public:
    explicit ClientController(int id, IPostRepository *post_repo, ICommentRepository *comment_repo, IUserRepository *user_repo):
        GuestController(post_repo, user_repo), _id(id), _comment_repo(comment_repo) {};

    CommentBL add_comment(const std::string& date, const std::string& text, int author_id, int post_id);
    std::string get_organizer(int post_id);
    std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                  const std::string& city, const std::string& author);
    UserBL update(const std::string& name, const std::string& surname, const std::string& login,
                  const std::string& password, const std::string& city);

protected:
    int _id;
    ICommentRepository *_comment_repo;
};

#endif  //CONTROLLER_CLIENT_H
