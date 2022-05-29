#ifndef REPOSITORY_POST_H
#define REPOSITORY_POST_H


#include "database/database.h"
#include "irepository/post.h"


class PostRepository: public IPostRepository
{
public:
    explicit PostRepository(IDataBase *db): _db(db) {};

    PostBL get_post(int post_id) override;
    std::vector<PostBL> get_posts() override;
    std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                  const std::string& city, const std::string& author) override;
    PostBL add_post(std::string name, int author_id, std::string information, std::string city,
                    std::string organizer, std::string date) override;
    PostBL delete_post(int post_id) override;
    PostBL update_post(int post_id, std::string name, std::string information,
                       std::string city, std::string date) override;

private:
    IDataBase *_db;
    PostBL post_to_post_bl(Post post);
};

#endif  // REPOSITORY_POST_H
