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

#endif //__MASTER_HPP__
