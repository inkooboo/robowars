#ifndef SHUTDOWN_FLAG_HPP
#define SHUTDOWN_FLAG_HPP

#  include <list>
#  include <thread>

#  include "noncopyable.hpp"

typedef std::function<void()> on_shut_down_func_t;

class shutdown_signal_t : private noncopyable_t
{
public:
    void subscribe(on_shut_down_func_t func)
    {
        std::lock_guard<std::mutex> scoped_lock(m_guard);

        m_handlers.push_back(func);
    }

    void emitt() const
    {
        for (auto &f: m_handlers)
        {
            f();
        }
    }

private:
    std::mutex m_guard;
    std::list<on_shut_down_func_t> m_handlers;
};

typedef int entry_point_t(int, char*[], shutdown_signal_t&);

#endif // SHUTDOWN_FLAG_HPP
