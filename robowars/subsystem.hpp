#ifndef SUBSYSTEM_HPP
#define SUBSYSTEM_HPP

#  include "noncopyable.hpp"

class master_t;

class subsystem_t : private noncopyable_t
{
    friend class master_t;
public:
    virtual ~subsystem_t() {}

    virtual void start() {}
    virtual void stop() {}

    master_t & master();
private:
    master_t *m_master;
};

#endif // SUBSYSTEM_HPP
