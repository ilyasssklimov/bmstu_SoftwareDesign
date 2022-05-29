#ifndef REPOSITORY_COMMENT_H
#define REPOSITORY_COMMENT_H

#include "database/database.h"
#include "irepository/comment.h"


class CommentRepository: public ICommentRepository
{
public:
    explicit CommentRepository(IDataBase *db): _db(db) {};

    CommentBL get_comment(int comment_id) override;
    int get_comment_id(CommentBL comment) override;
    CommentBL add_comment(std::string date, std::string text, int author_id, int post_id) override;
    CommentBL delete_comment(int comment_id) override;
    CommentBL update_comment(int comment_id, std::string date, std::string text) override;

private:
    IDataBase *_db;
    static CommentBL comment_to_comment_bl(Comment comment);
};


#endif  // REPOSITORY_COMMENT_H
