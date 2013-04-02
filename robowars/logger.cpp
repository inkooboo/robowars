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

namespace internal
{
    
    thread_local std::string tls_name;
    
    void do_log(log_level_t level, const std::string &str)
    {
        printf("%s %d %s\n", tls_name.c_str(), (int)level, str.c_str());
    }
    
} //namespace internal

void set_this_thread_log_name(const char *name)
{
    internal::tls_name = name;
}
