//
//  master.hpp
//  subsystems
//
//  Created by Andrey Kubarkov on 7/27/12.
//

#ifndef __MASTER_HPP__
# define __MASTER_HPP__

# include "subsystem.hpp"
# include "noncopyable.hpp"

# include <vector>
# include <cassert>
# include <memory>

template <typename ParentSystem>
class master_t : private noncopyable_t
{
public:
    template <typename SubsystemType, typename ImplSubsystemType = SubsystemType, typename... Args>  // ImplSubsystemType can be used in case of virtual inheritance
    inline void add_managed_subsystem(Args ...args);

    template <typename SubsystemType, typename... Args>
    inline void add_unmanaged_subsystem(Args ...args);

    template <typename SubsystemType>
    inline void add_external_subsystem(SubsystemType *raw_pointer);

    template <typename SubsystemType>
    inline SubsystemType & subsystem();

    inline void start();
    inline void stop();

    inline master_t();

private:
    std::vector<std::unique_ptr<subsystem_t>> m_subsystems;
};

// Implementation

template <typename ParentSystem>
inline void master_t<ParentSystem>::start()
{
    for (auto &subsystem : m_subsystems)
    {
        subsystem->start();
    }
}

template <typename ParentSystem>
inline void master_t<ParentSystem>::stop()
{
    for (auto &subsystem : m_subsystems)
    {
        subsystem->stop();
    }
}

template <typename ParentSystem>
inline master_t<ParentSystem>::master_t()
{
    static ParentSystem *checker = 0;
    assert(0 == checker && "already created");
    checker = (ParentSystem *)1;
}

namespace internal
{
    template <typename ParentSystem, typename SubsystemType>
    struct unique_instance_t
    {
        unique_instance_t() : instance(0) {}
        SubsystemType *instance;
    };

    template <typename ParentSystem, typename SubsystemType>
    inline SubsystemType ** subsystem_instance()
    {
        static unique_instance_t<ParentSystem, SubsystemType> unique;
        return &unique.instance;
    }

    template <typename SubsystemType>
    struct unmanaged_holder_t : public subsystem_t
    {
        template <typename... Args>
        inline unmanaged_holder_t(Args ...args) : holder(args...) {}
        SubsystemType holder;
    };
}

template <typename ParentSystem>
template <typename SubsystemType, typename ImplSubsystemType, typename... Args>
inline void master_t<ParentSystem>::add_managed_subsystem(Args ...args)
{
    SubsystemType **instance = internal::subsystem_instance<ParentSystem, SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");

    *instance = new ImplSubsystemType(args...);

    m_subsystems.push_back(std::unique_ptr<subsystem_t>(*instance));
}

template <typename ParentSystem>
template <typename SubsystemType, typename... Args>
inline void master_t<ParentSystem>::add_unmanaged_subsystem(Args ...args)
{
    SubsystemType **instance = internal::subsystem_instance<ParentSystem, SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");

    internal::unmanaged_holder_t<SubsystemType> *unmanaged_holder = new internal::unmanaged_holder_t<SubsystemType>(args...);
    *instance = &(unmanaged_holder->holder);
    m_subsystems.push_back(std::unique_ptr<subsystem_t>(unmanaged_holder));
}

template <typename ParentSystem>
template <typename SubsystemType>
inline void master_t<ParentSystem>::add_external_subsystem(SubsystemType *raw_pointer)
{
    SubsystemType **instance = internal::subsystem_instance<ParentSystem, SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");

    *instance = raw_pointer;
}

template <typename ParentSystem>
template <typename SubsystemType>
inline SubsystemType & master_t<ParentSystem>::subsystem()
{
    SubsystemType **instance = internal::subsystem_instance<ParentSystem, SubsystemType>();
    assert(*instance != 0 && "Instance for this  subsystem was never added!");

    return **instance;
}

#endif //__MASTER_HPP__
