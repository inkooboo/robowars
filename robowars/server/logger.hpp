#ifndef _LOGGER_HPP_
# define _LOGGER_HPP_

# include "master.hpp"

# include "noncopyable.hpp"

# include <string>
# include <sstream>
# include <memory>

class Logger : public subsystem_t
{
public:
    Logger();
    ~Logger();
};

enum log_level_t
{
    DEBUG = 1, TRACE = 2, CRITICAL = 3
};

namespace logger
{

    class ThreadName;

    namespace detail
    {

        /**
         * @brief Internal logging function which perform real logging action.
         */
        void log_str(const log_level_t level, const std::string &to_log);

        /**
         * @brief Useful temporary object that contains current logging message as stream.
         * @remarks
         *      Perform real logging on destruction when non-empty.
         */
        struct rvalue_string
        {
            std::ostringstream *str_;

            log_level_t level_;

            template<typename T>
            rvalue_string operator <<(const T &val)
            {
                *str_ << val;
                return *this;
            }

            rvalue_string() 
            	: str_(0) 
            {
            }
            
            rvalue_string(rvalue_string &other)
            {
            	this->str_ = other.str_;
            	other.str_ = 0;
            	this->level_ = other.level_;
            }
            
            ~rvalue_string()
            {
                try
                {
                    if (str_)
                    {
                        log_str(level_, str_->str());
                        delete str_;
                    }
                }
                catch (...)
                {
                }
            }
        };

    } //namespace detail

    /**
     * @brief Function construct logging stream.
     * @remarks
     *      Used for stream-style logging.
     */
    detail::rvalue_string log(const log_level_t level);

    /**
     * @brief Function perform direct logging of string to log.
     */
    void log(const log_level_t level, const std::string &text);

    /**
     * @brief Sets logging name for thread.
     * @remarks
     *      Uses thread local storage.
     */
    void set_thread_name(const std::string &name);

} //namespace logger

#endif //_LOGGER_HPP_