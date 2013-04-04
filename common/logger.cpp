//
//  cpp11_logger.cpp
//  new_logger
//
//  Created by inkooboo on 12/14/12.
//  Copyright (c) 2012 inkooboo. All rights reserved.
//

#include "logger.hpp"

#include "cpp_defs.hpp"

#include <cstdio>
#include <cstring>

namespace internal
{
    
    thread_local char tls_name[255] = {0};
    
    void do_log(log_level_t level, const std::string &str)
    {
        const char *lvl_name = 0;
        switch (level)
        {
        case debug:
            lvl_name = "debug";
            break;
        case trace:
            lvl_name = "trace";
            break;
        case critical:
            lvl_name = "critical";
            break;
        default:
            break;
        }

        fprintf(stderr, "{%s} <%s> %s\n", tls_name, lvl_name, str.c_str());
    }
    
    logging_stream_t::logging_stream_t(log_level_t level)
        : stream(std::make_shared<std::stringstream>())
        , level(level)
    {
    }

    logging_stream_t::~logging_stream_t()
    {
        do_log(level, stream->str());
    }

} //namespace internal

void set_this_thread_log_name(const char *name)
{
    strncpy(internal::tls_name, name, sizeof(internal::tls_name));
}

std::string get_this_thread_log_name()
{
    return internal::tls_name;
}
