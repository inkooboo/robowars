#ifndef MASTER_HPP
#define MASTER_HPP

#  include "subsystem.hpp"
#  include "noncopyable.hpp"

#  include <unordered_map>
#  include <string>
#  include <memory>
#  include <typeinfo>
#  include <cassert>

class master_t : private noncopyable_t
{
public:
    template <typename SubsystemType>
    void add_subsystem(SubsystemType *subsystem)
    {
        const char *name = typeid(SubsystemType).name();

        subsystem->m_master = this;

        m_subsystems[name] = std::unique_ptr<subsystem_t>(subsystem);
    }

    template <typename SubsystemType>
    SubsystemType & subsystem()
    {
        const char *name = typeid(SubsystemType).name();

        auto it = m_subsystems.find(name);

        assert(it != m_subsystems.end());

        SubsystemType *ret = static_cast<SubsystemType *>(it->second.get());

        assert(ret);

        return *ret;
    }

    master_t() : m_subsystems(1024) {}

    void start()
    {
        for (auto &pair : m_subsystems)
        {
            pair.second->start();
        }
    }

    void stop()
    {
        for (auto &pair : m_subsystems)
        {
            pair.second->stop();
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<subsystem_t>> m_subsystems;
};

#endif // MASTER_HPP
