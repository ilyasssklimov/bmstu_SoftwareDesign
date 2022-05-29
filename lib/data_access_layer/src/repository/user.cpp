#include "exception/exception.h"
#include "repository/user.h"

#include <utility>


std::vector<PostBL> UserRepository::get_posts_bl(const std::vector<int> &posts_ids)
{
    std::vector<PostBL> posts;
    for (auto &post_id: posts_ids)
    {
        Post post = _db->get_post(post_id);
        if (!post)
        {
            time_t time_now = time(nullptr);
            throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
        }
        PostBL post_bl(post.get_name(), post.get_author_id(), post.get_information(),
                       post.get_city(),post.get_organizer(), post.get_date());
        posts.push_back(post_bl);
    }

    return posts;
}


std::vector<int> UserRepository::get_posts_ids(const std::vector<PostBL> &posts_bl)
{
    std::vector<int> posts_ids;
    for (PostBL post_bl: posts_bl)
    {
        Post post(post_bl.get_name(), post_bl.get_author_id(), post_bl.get_information(),
                  post_bl.get_city(),post_bl.get_organizer(), post_bl.get_date());
        int post_id = _db->get_post_id(post);
        if (post_id == -1)
        {
            time_t time_now = time(nullptr);
            throw PostIdGetException(__FILE__, __LINE__, ctime(&time_now));
        }
        posts_ids.push_back(post_id);
    }

    return posts_ids;
}


UserBL UserRepository::user_to_user_bl(User user)
{
    std::vector<PostBL> posts = get_posts_bl(user.get_posts_ids());
    UserBL user_bl = UserBL(user.get_name(), user.get_surname(), user.get_login(),
                            user.get_password(),user.get_city(), user.get_access(), posts);

    return user_bl;
}


UserBL UserRepository::get_user(int user_id)
{
    User user = _db->get_user(user_id);
    if (!user)
    {
        time_t time_now = time(nullptr);
        throw UserGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(user);
}


bool UserRepository::check_user(const std::string &login, const std::string &password)
{
    User user = _db->get_user(login, password);
    return (bool) user;
}


std::vector<UserBL> UserRepository::get_users()
{
    std::vector<User> users = _db->get_users();
    if (users.empty())
    {
        time_t time_now = time(nullptr);
        throw UsersGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    std::vector<UserBL> users_bl;
    for (auto &user: users)
    {
        UserBL user_bl = user_to_user_bl(user);
        users_bl.push_back(user_bl);
    }

    return users_bl;
}


UserBL UserRepository::add_user(std::string name, std::string surname, std::string login,
                                std::string password, std::string city, std::string access)
{
    User user = _db->add_user(name, surname, login, password, city, access);
    if (!user)
    {
        time_t time_now = time(nullptr);
        throw UserAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(user);
}


UserBL UserRepository::delete_user(int user_id)
{
    User user = _db->delete_user(user_id);
    if (!user)
    {
        time_t time_now = time(nullptr);
        throw UserAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(user);
}


UserBL UserRepository::update_user(int user_id, std::string name, std::string surname, std::string login,
                                   std::string password, std::string city, std::vector<PostBL> posts, bool upd_posts)
{
    UserBL user = get_user(user_id);

    std::string upd_name;
    if (!name.empty())
        upd_name = name;
    else
        upd_name = user.get_name();

    std::string upd_surname;
    if (!surname.empty())
        upd_surname = surname;
    else
        upd_surname = user.get_surname();

    std::string upd_login;
    if (!login.empty())
        upd_login = login;
    else
        upd_login = user.get_login();

    std::string upd_password;
    if (!password.empty())
        upd_password = password;
    else
        upd_password = user.get_password();

    std::string upd_city;
    if (!city.empty())
        upd_city = city;
    else
        upd_city = user.get_city();

    std::vector<PostBL> upd_vector_posts;
    if (upd_posts)
        upd_vector_posts = posts;
    else
        upd_vector_posts = user.get_posts();

    std::vector<int> posts_ids = get_posts_ids(upd_vector_posts);
    User upd_user = _db->update_user(user_id, upd_name, upd_surname, upd_login,
                                     upd_password, upd_city, posts_ids);

    if (!upd_user)
    {
        time_t time_now = time(nullptr);
        throw UserUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(upd_user);
}


UserBL UserRepository::update_user(UserBL user, const std::string& name, const std::string& surname, const std::string& login,
                                   const std::string& password, const std::string& city, std::vector<PostBL> posts, bool upd_posts)
{
    std::string upd_name;
    if (!name.empty())
        upd_name = name;
    else
        upd_name = user.get_name();

    std::string upd_surname;
    if (!surname.empty())
        upd_surname = surname;
    else
        upd_surname = user.get_surname();

    std::string upd_login;
    if (!login.empty())
        upd_login = login;
    else
        upd_login = user.get_login();

    std::string upd_password;
    if (!password.empty())
        upd_password = password;
    else
        upd_password = user.get_password();

    std::string upd_city;
    if (!city.empty())
        upd_city = city;
    else
        upd_city = user.get_city();

    std::vector<PostBL> upd_vector_posts;
    if (upd_posts)
        upd_vector_posts = std::move(posts);
    else
        upd_vector_posts = user.get_posts();

    std::vector<int> posts_ids = get_posts_ids(user.get_posts());
    std::vector<int> posts_ids_upd = get_posts_ids(upd_vector_posts);
    User user_dal(user.get_name(), user.get_surname(), user.get_login(), user.get_password(),
                  user.get_city(), user.get_access(), posts_ids);

    User upd_user = _db->update_user(user_dal, upd_name, upd_surname, upd_login,
                                     upd_password, upd_city, posts_ids_upd);

    if (!upd_user)
    {
        time_t time_now = time(nullptr);
        throw UserUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(upd_user);
}