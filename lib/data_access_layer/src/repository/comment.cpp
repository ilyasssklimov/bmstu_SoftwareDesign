#include "exception/exception.h"
#include "repository/comment.h"


CommentBL CommentRepository::comment_to_comment_bl(Comment comment)
{
    CommentBL comment_bl = CommentBL(comment.get_date(), comment.get_text(),
                                     comment.get_author_id(), comment.get_post_id());

    return comment_bl;
}


CommentBL CommentRepository::get_comment(int comment_id)
{
    Comment comment = _db->get_comment(comment_id);
    if (!comment)
    {
        time_t time_now = time(nullptr);
        throw CommentGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return comment_to_comment_bl(comment);
}


int CommentRepository::get_comment_id(CommentBL comment)
{
    Comment comment_dal(comment.get_date(), comment.get_text(), comment.get_author_id(),
                        comment.get_post_id());
    int comment_id = _db->get_comment_id(comment_dal);

    if (comment_id == -1)
    {
        time_t time_now = time(nullptr);
        throw CommentGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return comment_id;
}


CommentBL CommentRepository::add_comment(std::string date, std::string text, int author_id, int post_id)
{
    Comment comment = _db->add_comment(date, text, author_id, post_id);
    if (!comment)
    {
        time_t time_now = time(nullptr);
        throw CommentAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return comment_to_comment_bl(comment);
}


CommentBL CommentRepository::delete_comment(int comment_id)
{
    Comment comment = _db->delete_comment(comment_id);
    if (!comment)
    {
        time_t time_now = time(nullptr);
        throw CommentDeleteException(__FILE__, __LINE__, ctime(&time_now));
    }

    return comment_to_comment_bl(comment);
}


CommentBL CommentRepository::update_comment(int comment_id, std::string date, std::string text)
{
    CommentBL user = get_comment(comment_id);

    std::string upd_date;
    if (!date.empty())
        upd_date = date;
    else
        upd_date = user.get_date();

    std::string upd_text;
    if (!text.empty())
        upd_text = text;
    else
        upd_text = user.get_text();

    Comment upd_comment = _db->update_comment(comment_id, upd_date, upd_text);

    if (!upd_comment)
    {
        time_t time_now = time(nullptr);
        throw CommentUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return comment_to_comment_bl(upd_comment);
}