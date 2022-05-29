#include "exception/exception.h"
#include "repository/post.h"



PostBL PostRepository::post_to_post_bl(Post post)
{
    PostBL post_bl = PostBL(post.get_name(), post.get_author_id(), post.get_information(),
                            post.get_city(), post.get_organizer(), post.get_date());

    return post_bl;
}



PostBL PostRepository::get_post(int post_id)
{
    Post post = _db->get_post(post_id);
    if (!post)
    {
        time_t time_now = time(nullptr);
        throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(post);
}


std::vector<PostBL> PostRepository::get_posts()
{
    std::vector<Post> posts = _db->get_posts();
    if (posts.empty())
    {
        time_t time_now = time(nullptr);
        throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    std::vector<PostBL> posts_bl;
    for (auto &post: posts)
    {
        PostBL post_bl = post_to_post_bl(post);
        posts_bl.push_back(post_bl);
    }

    return posts_bl;
}


std::vector<PostBL> PostRepository::get_posts(const std::string& date, const std::string& name,
                                              const std::string& city, const std::string& author)
{
    int author_id = _db->get_user_id(author);
    std::vector<Post> posts = _db->get_posts(date, name, city, author_id);
    if (posts.empty())
    {
        time_t time_now = time(nullptr);
        throw PostsGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    std::vector<PostBL> posts_bl;
    for (auto &post: posts)
    {
        PostBL post_bl = post_to_post_bl(post);
        posts_bl.push_back(post_bl);
    }

    return posts_bl;
}


PostBL PostRepository::add_post(std::string name, int author_id, std::string information, std::string city,
                                std::string organizer, std::string date)
{
    Post post = _db->add_post(name, author_id, information, city, organizer, date);
    if (!post)
    {
        time_t time_now = time(nullptr);
        throw PostAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(post);
}


PostBL PostRepository::delete_post(int post_id)
{
    Post post = _db->delete_post(post_id);
    if (!post)
    {
        time_t time_now = time(nullptr);
        throw PostDeleteException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(post);
}


PostBL PostRepository::update_post(int post_id, std::string name, std::string information,
                                   std::string city, std::string date)
{
    PostBL user = get_post(post_id);

    std::string upd_name;
    if (!name.empty())
        upd_name = name;
    else
        upd_name = user.get_name();

    std::string upd_information;
    if (!information.empty())
        upd_information = information;
    else
        upd_information = user.get_information();

    std::string upd_city;
    if (!city.empty())
        upd_city = city;
    else
        upd_city = user.get_city();

    std::string upd_date;
    if (!date.empty())
        upd_date = date;
    else
        upd_date = user.get_date();

    Post upd_post = _db->update_post(post_id, upd_name, upd_information, upd_city, upd_date);

    if (!upd_post)
    {
        time_t time_now = time(nullptr);
        throw UserUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(upd_post);
}
