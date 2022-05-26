#include "controller/author.h"
#include "logger/logger.h"
#include "exception/exception.h"


PostBL AuthorController::create_post(const std::string &name, const std::string &info, const std::string &city,
                                   const std::string &organizer, const std::string &date)
{
    PostBL post(name, _id, info, city, organizer, date);

    try
    {
        std::vector<UserBL> users = _user_repo->get_users();
        for (UserBL user: users)
            if (user.get_access() == "admin") {
                std::vector<PostBL> posts = user.get_posts();
                posts.push_back(post);
                _user_repo->update_user(user, "", "", "", "", "", posts, true);

                log_info("Create post with title \"" + name + "\"");
                return post;
            }

        time_t time_now = time(nullptr);
        throw AdminFindException(__FILE__, __LINE__, ctime(&time_now));
    }
    catch (UsersGetException &e)
    {
        log_error(e.what());
    }
    catch (UserUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to add new post to admin entity while creating post with title \"" + name + "\"");
    }
    catch (AdminFindException &e)
    {
        log_error(e.what());
        log_error("Unable to find admin while creating post by author with id = " + std::to_string(_id));
    }
    catch (...)
    {
        log_error("Some error while creating post by author with id = " + std::to_string(_id));
    }

    return {};
}
