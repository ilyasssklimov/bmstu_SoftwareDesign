#include <iostream>
#include "database/pg_database.h"
#include "logger.h"


static std::vector<int> string_to_posts(const std::string &string_posts_ids)
{
    if (string_posts_ids.empty())
        return {};

    std::vector<int> posts_ids;
    std::vector<std::string> tokens;
    std::string token;

    std::stringstream stream_ids(string_posts_ids.substr(1, string_posts_ids.find('}') - 1));
    while (getline(stream_ids, token, ','))
        posts_ids.push_back(std::stoi(token));

    return posts_ids;
}


static std::string posts_to_string(const std::vector<int> &posts_ids)
{
    std::string string_posts_ids = "{";
    for (auto &post_id: posts_ids)
        string_posts_ids += std::to_string(post_id) + ",";
    string_posts_ids = string_posts_ids.substr(0, string_posts_ids.rfind(',')) + "}";

    return string_posts_ids;
}


std::vector<User> PGDatabase::get_users()
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.user");
    connection.disconnect();

    if (response.empty())
    {
        log_error("Response of getting all users from DB is empty");
        return {};
    }

    log_info("Get all users from PostgreSQL DB");
    std::vector<User> users;

    for (const auto &user_db : response)
    {
        std::string string_ids = pqxx::to_string(user_db[7]);
        std::vector<int> posts_ids = string_to_posts(string_ids);
        User user(pqxx::to_string(user_db[1]), pqxx::to_string(user_db[2]),
                  pqxx::to_string(user_db[3]), pqxx::to_string(user_db[4]),
                  pqxx::to_string(user_db[5]),pqxx::to_string(user_db[6]), posts_ids);

        users.push_back(user);
    }

    return users;
}


User PGDatabase::get_user(int user_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.user WHERE id = " + std::to_string(user_id));
    connection.disconnect();

    if (response.empty())
    {
        log_error("Unable to find user from DB with id = " + std::to_string(user_id));
        return {};
    }

    log_info("Get user from DB with id = " + std::to_string(user_id));

    std::string string_ids = pqxx::to_string(response[0][7]);
    std::vector<int> posts_ids = string_to_posts(string_ids);
    User user(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]),pqxx::to_string(response[0][6]), posts_ids);

    return user;
}

int PGDatabase::get_user_id(const std::string &login)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.user WHERE login = \'" + login + "\'");
    connection.disconnect();

    if (response.empty())
    {
        log_error("Unable to find user from DB with name = " + login);
        return -1;
    }

    log_info("Get id of user from DB with name = " + login);
    return std::stoi(pqxx::to_string(response[0][0]));
}


User PGDatabase::get_user(const std::string &login, const std::string &password)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.user WHERE login = \'" + login + "\' AND password = \'" + password + "\'"
    );
    connection.disconnect();

    if (response.empty())
    {
        log_error("Unable to find user from DB with login = " + login + " and password = " + password);
        return {};
    }

    log_info("Get user from DB with login = " + login + " and password = " + password);
    std::string string_ids = pqxx::to_string(response[0][7]);
    std::vector<int> posts_ids = string_to_posts(string_ids);
    User user(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]),pqxx::to_string(response[0][6]), posts_ids);

    return user;
}


User PGDatabase::add_user(std::string name, std::string surname, std::string login,
                          std::string password, std::string city, std::string access)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.user WHERE login = \'" + login + "\'"
    );

    if (!response.empty())
    {
        log_error("Unable to add user to DB with login = " + login);
        return {};
    }

    worker.exec("INSERT INTO software.public.user (name, surname, login, password, city, access) "
                "VALUES (\'" + name + "\', \'" + surname + "\', \'" + login + "\', \'" + password +
                "\', \'" + city + "\', \'" + access + "\')");
    worker.commit();
    connection.disconnect();

    log_info("Add user to DB with login = " + login);
    User user(name, surname, login, password, city, access);
    return user;
}


User PGDatabase::delete_user(int user_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.user WHERE id = " + std::to_string(user_id)
    );

    if (response.empty())
    {
        log_error("Unable to delete user from DB with id = " + std::to_string(user_id));
        return {};
    }

    std::string string_ids = pqxx::to_string(response[0][7]);
    std::vector<int> posts_ids = string_to_posts(string_ids);
    User user(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]), posts_ids);

    worker.exec("DELETE FROM software.public.user WHERE id = " + std::to_string(user_id));
    worker.commit();
    connection.disconnect();

    log_info("Delete user from DB with id = " + std::to_string(user_id));
    return user;
}


User PGDatabase::update_user(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                             const std::string& password, const std::string& city, const std::vector<int>& posts)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.user WHERE id = " + std::to_string(user_id)
    );

    if (response.empty())
    {
        log_error("Unable to update user from DB with id = " + std::to_string(user_id));
        return {};
    }
    User user(name, surname, login, password, city, pqxx::to_string(response[0]["access"]), posts);

    worker.exec("UPDATE software.public.user SET name = \'" + name + "\', surname = \'" + surname +
                "\', login = \'" + login + "\', password = \'" + password + "\', city = \'" + city +
                "\', posts_ids = \'" + posts_to_string(posts) + "\' WHERE id = " + std::to_string(user_id));
    worker.commit();
    connection.disconnect();

    log_info("UPDATE user from DB with id = " + std::to_string(user_id));
    return user;
}


User PGDatabase::update_user(User user, const std::string &name, std::string surname, std::string login,
                             const std::string &password, const std::string &city, const std::vector<int> &posts)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.user WHERE login = \'" + user.get_login() +
            "\' and password = \'" + user.get_password() + "\'"
    );

    if (response.empty())
    {
        log_error("Unable to update user from DB with login = " + user.get_login());
        return {};
    }
    User upd_user(name, surname, login, password, city, pqxx::to_string(response[0]["access"]), posts);

    worker.exec("UPDATE software.public.user SET name = \'" + name + "\', surname = \'" + surname +
                "\', login = \'" + login + "\', password = \'" + password + "\', city = \'" + city +
                "\', posts_ids = \'" + posts_to_string(posts) + "\' WHERE login = \'" + user.get_login()
                + "\' and password = \'" + user.get_password() + "\'");
    worker.commit();
    connection.disconnect();

    log_info("UPDATE user from DB with login = " + user.get_login());
    return upd_user;
}


std::vector<Post> PGDatabase::get_posts()
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.post");
    connection.disconnect();

    if (response.empty())
    {
        log_error("Response of getting all posts from DB is empty");
        return {};
    }

    log_info("Get all posts from PostgreSQL DB");
    std::vector<Post> posts;

    for (const auto &post_db : response)
    {
        Post post(pqxx::to_string(post_db[1]), std::stoi(pqxx::to_string(post_db[2])),
                  pqxx::to_string(post_db[3]), pqxx::to_string(post_db[4]),
                  pqxx::to_string(post_db[5]), pqxx::to_string(post_db[6]));
        posts.push_back(post);
    }

    return posts;
}


Post PGDatabase::get_post(int post_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.post WHERE id = " + std::to_string(post_id));
    connection.disconnect();

    if (response.empty())
    {
        log_error("Unable to find post from DB with id = " + std::to_string(post_id));
        return {};
    }

    log_info("Get post from DB with id = " + std::to_string(post_id));
    Post post(pqxx::to_string(response[0][1]), std::stoi(pqxx::to_string(response[0][2])),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]));

    return post;
}


int PGDatabase::get_post_id(Post post)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.post WHERE name = \'" +
                                        post.get_name() + "\' AND author_id = " + std::to_string(post.get_author_id()) +
                                        " AND information = \'" + post.get_information() + "\' AND city = \'" + post.get_city() +
                                        "\' AND organizer = \'" + post.get_organizer() + "\' AND date = \'" + post.get_date() + "\'");
    connection.disconnect();

    if (response.empty())
    {
        log_error("Unable to find post from DB with name = " + post.get_name());
        return -1;
    }

    log_info("Get id of post from DB with name = " + post.get_name());
    return std::stoi(pqxx::to_string(response[0][0]));
}


std::vector<Post> PGDatabase::get_posts(const std::string& date, const std::string& name,
                                        const std::string& city, int author)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.post WHERE date = \'" + date + "\' OR name = \'" + name +
            "\' OR city = \'" + city + "\' OR author_id = " + std::to_string(author)
    );
    connection.disconnect();

    if (response.empty())
    {
        log_error("Response of getting posts with filters from DB is empty");
        return {};
    }

    log_info("Get posts with filters from PostgreSQL DB");
    std::vector<Post> posts;

    for (const auto &post_db : response)
    {
        Post post(pqxx::to_string(post_db[1]), std::stoi(pqxx::to_string(post_db[2])),
                  pqxx::to_string(post_db[3]), pqxx::to_string(post_db[4]),
                  pqxx::to_string(post_db[5]), pqxx::to_string(post_db[6]));
        posts.push_back(post);
    }

    return posts;
}


Post PGDatabase::add_post(std::string name, int author_id, std::string information, std::string city,
                          std::string organizer, std::string date)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.post WHERE name = \'" + name + "\'"
    );

    if (!response.empty())
    {
        log_error("Unable to add post to DB with name = " + name);
        return {};
    }

    worker.exec("INSERT INTO software.public.post (name, author_id, information, city, organizer, date) "
                "VALUES (\'" + name + "\', " + std::to_string(author_id) + ", \'" + information +
                "\', \'" + city + "\', \'" + organizer + "\', \'" + date + "\')");
    worker.commit();
    connection.disconnect();

    log_info("Add post to DB with login = " + name);
    Post post(name, author_id, information, city, organizer, date);
    return post;
}

Post PGDatabase::delete_post(int post_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.post WHERE id = " + std::to_string(post_id)
    );

    if (response.empty())
    {
        log_error("Unable to delete post from DB with id = " + std::to_string(post_id));
        return {};
    }

    Post post(pqxx::to_string(response[0][1]), std::stoi(pqxx::to_string(response[0][2])),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]));

    worker.exec("DELETE FROM software.public.post WHERE id = " + std::to_string(post_id));
    worker.commit();
    connection.disconnect();

    log_info("Delete post from DB with id = " + std::to_string(post_id));
    return post;
}


Post PGDatabase::update_post(int post_id, std::string name, std::string information,
                             std::string city, std::string date)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.post WHERE id = " + std::to_string(post_id)
    );

    if (response.empty())
    {
        log_error("Unable to update post from DB with id = " + std::to_string(post_id));
        return {};
    }
    Post post(name, std::stoi(pqxx::to_string(response[0]["author_id"])), information,
              city, pqxx::to_string(response[0]["organizer"]), date);

    worker.exec("UPDATE software.public.post SET name = \'" + name + "\', information = \'" + information +
                "\', city = \'" + city + "\', date = \'" + date + "\' WHERE id = " + std::to_string(post_id));
    worker.commit();
    connection.disconnect();

    log_info("UPDATE post from DB with id = " + std::to_string(post_id));
    return post;
}


Comment PGDatabase::get_comment(int comment_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec("SELECT * FROM software.public.comment WHERE id = " + std::to_string(comment_id));
    connection.disconnect();

    if (response.empty())
    {
        log_error("Unable to find comment from DB with id = " + std::to_string(comment_id));
        return {};
    }

    log_info("Get comment from DB with id = " + std::to_string(comment_id));
    Comment comment(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
                    std::stoi(pqxx::to_string(response[0][3])), std::stoi(pqxx::to_string(response[0][4])));

    return comment;
}


Comment PGDatabase::add_comment(std::string date, std::string text, int author_id, int post_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);

    worker.exec("INSERT INTO software.public.comment (date, text, author_id, post_id) "
                "VALUES (\'" + date + "\', \'" + text + "\', " + std::to_string(author_id) +
                ", " + std::to_string(post_id) + ")");
    worker.commit();
    connection.disconnect();

    log_info("Add comment to DB with post_id = " + std::to_string(post_id));
    Comment comment(date, text, author_id, post_id);
    return comment;
}


Comment PGDatabase::delete_comment(int comment_id)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.comment WHERE id = " + std::to_string(comment_id)
    );

    if (response.empty())
    {
        log_error("Unable to delete comment from DB with id = " + std::to_string(comment_id));
        return {};
    }

    Comment comment(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
                    std::stoi(pqxx::to_string(response[0][3])), std::stoi(pqxx::to_string(response[0][4])));

    worker.exec("DELETE FROM software.public.comment WHERE id = " + std::to_string(comment_id));
    worker.commit();
    connection.disconnect();

    log_info("Delete comment from DB with id = " + std::to_string(comment_id));
    return comment;
}


Comment PGDatabase::update_comment(int comment_id, std::string date, std::string text)
{
    pqxx::connection connection(_params.c_str());
    pqxx::work worker(connection);
    pqxx::result response = worker.exec(
            "SELECT * FROM software.public.comment WHERE id = " + std::to_string(comment_id)
    );

    if (response.empty())
    {
        log_error("Unable to update comment from DB with id = " + std::to_string(comment_id));
        return {};
    }
    Comment comment(date, text, std::stoi(pqxx::to_string(response[0][3])),
                    std::stoi(pqxx::to_string(response[0][4])));

    worker.exec("UPDATE software.public.comment SET date = \'" + date + "\', text = \'" + text +
                "\' WHERE id = " + std::to_string(comment_id));
    worker.commit();
    connection.disconnect();

    log_info("UPDATE comment from DB with id = " + std::to_string(comment_id));
    return comment;
}
