#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>
#include <exception>


class BaseException: public std::exception
{
public:
    BaseException(const std::string &filename, const int line, const char *time, const std::string &message)
    {
        error = "Error! " + message + "\n" + time + "Filename: " + filename + ", line # " + std::to_string(line) + ". ";
    }

    const char *what() const noexcept override
    {
        return error.c_str();
    }

protected:
    std::string error;
};


class PostGetException: public BaseException
{
public:
    PostGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get post.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class PostIdGetException: public BaseException
{
public:
    PostIdGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get post id.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class PostsGetException: public BaseException
{
public:
    PostsGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get all post.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class PostDeleteException: public BaseException
{
public:
    PostDeleteException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to delete post.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class PostsFilterGetException: public BaseException
{
public:
    PostsFilterGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get posts with filters.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class CommentAddException: public BaseException
{
public:
    CommentAddException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to add comment.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class PostAddException: public BaseException
{
public:
    PostAddException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to add post.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class UserGetException: public BaseException
{
public:
    UserGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get user.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class UsersGetException: public BaseException
{
public:
    UsersGetException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to get all users.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class UserAddException: public BaseException
{
public:
    UserAddException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to add user.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class UserUpdateException: public BaseException
{
public:
    UserUpdateException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to update user.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class UserDeleteException: public BaseException
{
public:
    UserDeleteException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to delete user.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


class AdminFindException: public BaseException
{
public:
    AdminFindException(const std::string &filename, const int line, const char *time):
    BaseException(filename, line, time, "Unable to find admin.") {};

    const char *what() const noexcept override
    {
        return error.c_str();
    }
};


#endif  // EXCEPTION_H
