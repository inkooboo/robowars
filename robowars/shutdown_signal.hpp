#ifndef SHUTDOWN_FLAG_HPP
#define SHUTDOWN_FLAG_HPP

#  include <memory>

class shutdown_signal_t
{
public:
    shutdown_signal_t() : m_signal(new bool(false)) {}

    bool is_set() const
    {
        return *m_signal;
    }

    void set()
    {
        *m_signal = true;
    }

private:
    std::shared_ptr<bool> m_signal;
};

typedef int entry_point_t(int, char*[], shutdown_signal_t);

#endif // SHUTDOWN_FLAG_HPP
