#include "controller/client.h"
#include "logger.h"
#include "exception/exception.h"


CommentBL ClientController::add_comment(const std::string &date, const std::string& text, int author_id, int post_id)
{
    try
    {
        CommentBL comment = _comment_repo->add_comment(date, text, author_id, post_id);
        log_info("Add post with text \"" + comment.get_text() + "\"");
        return comment;
    }
    catch (CommentAddException &e)
    {
        log_error(e.what());
        log_error("Unable to add post with text \"" + text + "\"");
    }
    catch (...)
    {
        log_error("Some error while adding comment with text \"" + text + "\"");
    }

    return {};
}


std::string ClientController::get_organizer(int post_id)
{
    PostBL post = get_post(post_id);
    if (post)
    {
        log_info("Get organizer from post with title " + post.get_name());
        return post.get_organizer();
    }
    else
    {
        log_error("Unable to get post with id = " + std::to_string(post_id) + " while getting post organizer");
        return "";
    }
}


std::vector<PostBL> ClientController::get_posts(const std::string& data="", const std::string& name="",
                                                const std::string& city="", const std::string& author="")
{
    try
    {
        std::vector<PostBL> post_vector = _post_repo->get_posts(data, name, city, author);
        log_info("Get posts with filters");
        return post_vector;
    }
    catch (PostsFilterGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting posts with filters");
    }

    return {};
}


UserBL ClientController::update(const std::string& name, const std::string& surname, const std::string& login,
                                const std::string& password, const std::string& city)
{
    try
    {
        UserBL updating_user = _user_repo->update_user(_id, name, surname, login, password, city, {}, false);
        log_info("Update user with id = " + std::to_string(_id));
        return updating_user;
    }
    catch (UserUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to update user with id = " + std::to_string(_id));
    }
    catch (...)
    {
        log_error("Some error while updating user with id = " + std::to_string(_id));
    }

    return {};
}