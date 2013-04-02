//
//  cpp11_logger.h
//  new_logger
//
//  Created by inkooboo on 12/14/12.
//  Copyright (c) 2012 inkooboo. All rights reserved.
//

#ifndef __new_logger__cpp11_logger__
#define __new_logger__cpp11_logger__

#  include <sstream>

enum log_level_t
{
      NO_LOG = -1
    , debug
    , trace
    , critical
    , LAST_LOG
};

namespace internal
{
    void do_log(log_level_t level, const std::string &str);

    struct logging_stream_t
    {
        logging_stream_t(logging_stream_t&&) = default;

        explicit logging_stream_t(log_level_t level)
            : level(level)
        {
        }
        
        ~logging_stream_t()
        {
            do_log(level, stream.str());
        }
                
        template <typename T>
        logging_stream_t & operator<<(const T &val)
        {
            const static log_level_t min_log_level =
#ifdef DEBUG
                debug;
#else
                trace;
#endif
            if (level >= min_log_level)
            {
                stream << val;
            }
            
            return *this;
        }

    private:
        std::stringstream stream;
        log_level_t level;
    };    

} //namespace internal

void set_this_thread_log_name(const char *name);
std::string get_this_thread_log_name();

template <log_level_t LogLevel>
inline internal::logging_stream_t log()
{
    static_assert(LogLevel > NO_LOG, "wrong log level");
    static_assert(LogLevel < LAST_LOG, "wrong log level");
    return internal::logging_stream_t(LogLevel);
}


#endif /* defined(__new_logger__cpp11_logger__) */
