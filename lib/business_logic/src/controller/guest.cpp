#include "controller/guest.h"
#include "logger.h"
#include "exception/exception.h"


UserBL GuestController::sign_in(const std::string &name, const std::string &surname, const std::string &login,
                                const std::string &password, const std::string &city, const std::string &access)
{
    try
    {
        UserBL user = _user_repo->add_user(name, surname, login, password, city, access);
        log_info("New user with login \"" + login + "\" registered");
        return user;
    }
    catch (UserAddException &e)
    {
        log_error(e.what());
        log_error("Unable to register user with login \"" + login + "\"");
    }
    catch (...)
    {
        log_error("Some error during registration user with login \"" + login + "\"");
    }

    return {};
}


bool GuestController::log_in(const std::string &login, const std::string &password)
{
    if (_user_repo->check_user(login, password))
    {
        log_info("User with login \"" + login + "\" successfully logged in");
        return true;
    }
    else
    {
        log_error("User input incorrect login and / or password");
        return false;
    }
}

PostBL GuestController::get_post(int post_id)
{
    try
    {
        PostBL post = _post_repo->get_post(post_id);
        log_info("Get post with title " + post.get_name());
        return post;
    }
    catch (PostGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get post with id = " + std::to_string(post_id) + " while getting post");
    }
    catch (...)
    {
        log_error("Some error while getting post with id " + std::to_string(post_id));
    }

    return {};
}


std::vector<PostBL> GuestController::get_posts(std::vector<int> &post_ids)
{
    if (post_ids.empty())
    {
        log_error("Vector of post ids for getting posts is empty");
        return {};
    }

    std::vector<PostBL> post_vector;
    PostBL post;

    log_info("Try to get posts by ids");
    for (int post_id: post_ids)
    {
        post = get_post(post_id);
        if (post)
            post_vector.push_back(post);
    }

    return post_vector;
}


std::vector<PostBL> GuestController::get_posts()
{
    try
    {
        std::vector<PostBL> post_vector = _post_repo->get_posts();
        log_info("Get all posts");
        return post_vector;
    }
    catch (PostsGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting all posts");
    }

    return {};
}


std::string GuestController::get_post_info(int post_id)
{
    PostBL post = get_post(post_id);
    if (post)
    {
        log_info("Get information from post with title " + post.get_name());
        return post.get_information();
    }
    else
    {
        log_error("Unable to get post with id = " + std::to_string(post_id) + " while getting post info");
        return "";
    }
}