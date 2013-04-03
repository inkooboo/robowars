//
//  master.hpp
//  subsystems
//
//  Created by Andrey Kubarkov on 7/27/12.
//

#ifndef __MASTER_HPP__
#  define __MASTER_HPP__

#  include "noncopyable.hpp"

#  define DEFINE_SUBSYSTEM(SubsystemType, GetterName) \
    public: SubsystemType & GetterName() { return m_#GetterName} \
    private: SubsystemType m_#GetterName;


class master_base_t : private noncopyable_t
{
public:
    inline master_t() {}
    inline virtual ~master_t() {}
};

#endif //__MASTER_HPP__
