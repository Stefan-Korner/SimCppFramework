//*****************************************************************************
// (C) 2014, Stefan Korner, Austria                                           *
//                                                                            *
// The Sim C++ Framework is free software; you can redistribute it and/or     *
// modify it under the terms of the GNU Lesser General Public License as      *
// published by the Free Software Foundation; either version 2.1 of the       *
// License, or (at your option) any later version.                            *
//                                                                            *
// The Sim C++ Framework is distributed in the hope that it will be useful,   *
// but WITHOUT ANY WARRANTY; without even the implied warranty of             *
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser    *
// General Public License for more details.                                   *
//*****************************************************************************
// Scheduler                                                                  *
//*****************************************************************************
#include "SCHED_Scheduler.hpp"

// global variables
SCHED::Scheduler* SCHED::Scheduler::s_instance = NULL;

//////////
// Task //
//////////

//-----------------------------------------------------------------------------
SCHED::Task::Task(uint32_t p_taskCycle, uint32_t p_startDelay)
//-----------------------------------------------------------------------------
{
  SCHED::Scheduler::instance()->registerTask(this, p_taskCycle, p_startDelay);
}

//-----------------------------------------------------------------------------
SCHED::Task::~Task()
//-----------------------------------------------------------------------------
{
  SCHED::Scheduler::instance()->unregisterTask(this);
}

///////////////
// Scheduler //
///////////////

//-----------------------------------------------------------------------------
SCHED::Scheduler::Scheduler(): m_active(false)
//-----------------------------------------------------------------------------
{
  s_instance = this;
}

//-----------------------------------------------------------------------------
SCHED::Scheduler::~Scheduler()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::start()
//-----------------------------------------------------------------------------
{
  m_active = true;
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::stop()
//-----------------------------------------------------------------------------
{
  m_active = false;
}

//-----------------------------------------------------------------------------
bool SCHED::Scheduler::isActive() const
//-----------------------------------------------------------------------------
{
  return m_active;
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::registerTask(SCHED::Task* p_task,
                                    uint32_t p_taskCycle,
                                    uint32_t p_startDelay)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::unregisterTask(SCHED::Task* p_task)
//-----------------------------------------------------------------------------
{}

