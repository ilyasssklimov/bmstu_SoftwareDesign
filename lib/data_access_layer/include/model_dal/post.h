#ifndef DAL_POST_H
#define DAL_POST_H

#include <iostream>
#include <string>
#include <utility>


class Post
{
public:
    Post(std::string name, int author_id, std::string information, std::string city, std::string organizer, std::string date):
         _name(std::move(name)), _author_id(author_id), _information(std::move(information)),
         _city(std::move(city)), _organizer(std::move(organizer)), _date(std::move(date)) {};
    Post(): _author_id(-1) {};

    std::string get_name();
    int get_author_id() const;
    std::string get_information();
    std::string get_city();
    std::string get_organizer();
    std::string get_date();

    void set_name(const std::string &value);
    void set_information(const std::string &value);
    void set_city(const std::string &value);
    void set_date(const std::string &value);

    explicit operator bool() const { return _author_id != -1; }
    bool operator == (Post post) const
    {
        return post.get_name() == _name &&
        post.get_author_id() == _author_id &&
        post.get_information() == _information &&
        post.get_city() == _city &&
        post.get_organizer() == _organizer &&
        post.get_date() == _date;
    }

private:
    std::string _name;
    int _author_id;
    std::string _information;
    std::string _city;
    std::string _organizer;
    std::string _date;
};


#endif  // DAL_POST_H
