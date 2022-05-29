#include <algorithm>
#include "controller/admin.h"
#include "logger.h"
#include "exception/exception.h"


PostBL AdminController::submit_post(PostBL post)
{
    try
    {
        PostBL adding_post = _post_repo->add_post(post.get_name(), post.get_author_id(), post.get_information(),
                                                  post.get_city(), post.get_organizer(), post.get_date());

        UserBL user = _user_repo->get_user(_id);
        std::vector<PostBL> posts = user.get_posts();
        posts.erase(std::remove(posts.begin(), posts.end(), post), posts.end());
        _user_repo->update_user(_id, "", "", "", "", "", posts, true);

        log_info("Submit post with title \"" + post.get_name() + "\"");
        return adding_post;
    }
    catch (PostAddException &e)
    {
        log_error(e.what());
        log_error("Unable to add post with title \"" + post.get_name() + "\"");
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get user with id = " + std::to_string(_id) + " while submitting post");
    }
    catch (UserUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to update user with id = " + std::to_string(_id) + " while submitting post");
    }
    catch (...)
    {
        log_error("Some error while submitting post");
    }

    return {};
}


UserBL AdminController::delete_user(int user_id)
{
    try
    {
        UserBL user = _user_repo->get_user(user_id);
        _user_repo->delete_user(user_id);
        log_info("Delete user with id " + std::to_string(user_id));

        return user;
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
        log_error("Unable to find user with id " + std::to_string(user_id) + " while deleting user");
    }
    catch (UserDeleteException &e)
    {
        log_error(e.what());
        log_error("Unable to delete user with id " + std::to_string(user_id));
    }
    catch (...)
    {
        log_error("Some error while deleting user");
    }

    return {};
}
