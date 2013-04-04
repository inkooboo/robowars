#ifndef USER_INFO_HPP
#  define USER_INFO_HPP

#  include "noncopyable.hpp"

#  include <string>

class user_info_t : private noncopyable_t
{
public:
    std::string user_name;

};


#endif // USER_INFO_HPP
