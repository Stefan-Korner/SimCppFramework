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

#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>

// global variables
SCHED::Scheduler* SCHED::Scheduler::s_instance = NULL;

//////////
// Task //
//////////

//-----------------------------------------------------------------------------
SCHED::Task::Task(uint32_t p_position,
                  uint32_t p_taskCycle,
                  uint32_t p_startDelay)
//-----------------------------------------------------------------------------
{
  SCHED::Scheduler::instance()
    ->registerTask(this, p_position, p_taskCycle, p_startDelay);
}

//-----------------------------------------------------------------------------
SCHED::Task::~Task()
//-----------------------------------------------------------------------------
{
  SCHED::Scheduler::instance()->unregisterTask(this);
}

///////////////////
// SchedulerImpl //
///////////////////

namespace SCHED
{
  //---------------------------------------------------------------------------
  struct TaskEntry
  //---------------------------------------------------------------------------
  {
    Task* m_task;
    uint32_t m_taskCycle;
    uint32_t m_startDelay;
    uint64_t m_nextExecTime;
    TaskEntry():
      m_task(NULL), m_taskCycle(0), m_startDelay(0), m_nextExecTime(0) {}
  };

  //---------------------------------------------------------------------------
  class SchedulerImpl
  //---------------------------------------------------------------------------
  {
  public:
    uint32_t m_maxTasks;
    bool m_active;
    pthread_t m_threadID;
    uint64_t m_simulationTime;
    uint64_t m_nextScheduleTime;
    uint32_t m_slowDownFactor;
    TaskEntry* m_tasks;
    SchedulerImpl(uint32_t p_maxTasks): m_maxTasks(p_maxTasks),
                                        m_active(false),
                                        m_simulationTime(0),
                                        m_nextScheduleTime(0xFFFFFFFFFFFFFFFF),
                                        m_slowDownFactor(1),
                                        m_tasks(NULL)
    {
      m_tasks = new TaskEntry[p_maxTasks];
    }
    ~SchedulerImpl()
    {
      delete[] m_tasks;
    }
    void schedule()
    {
      m_nextScheduleTime += 0xFFFFFFFF;
      for(uint32_t i = 0; i < m_maxTasks; i++)
      {
        TaskEntry& nextTaskEntry = m_tasks[i];
        // execute the next task on demand
        if((nextTaskEntry.m_task != NULL) &&
           (nextTaskEntry.m_nextExecTime <= m_simulationTime))
        {
          nextTaskEntry.m_task->exec(m_simulationTime);
          nextTaskEntry.m_nextExecTime += nextTaskEntry.m_taskCycle;
        }
        // the next schedule time is the earliest next execute time
        if((nextTaskEntry.m_task != NULL) &&
           (nextTaskEntry.m_nextExecTime < m_nextScheduleTime))
        {
          m_nextScheduleTime = nextTaskEntry.m_nextExecTime;
        }
      }
    }
  };
}

// singleton implementation
static SCHED::SchedulerImpl* s_impl = NULL;

//-----------------------------------------------------------------------------
static uint64_t getTimeOfDay()
//-----------------------------------------------------------------------------
{
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  uint64_t retVal = tv.tv_sec;
  retVal *= 1000000;
  retVal += tv.tv_usec;
  return retVal;
}

//-----------------------------------------------------------------------------
static void sleepRel(uint64_t p_sleepTime)
//-----------------------------------------------------------------------------
{
  struct timeval sleepTime;
  sleepTime.tv_sec = (uint32_t) p_sleepTime / 1000000;
  sleepTime.tv_usec = (uint32_t) p_sleepTime % 1000000;
  select(FD_SETSIZE, NULL, NULL, NULL, &sleepTime);
}

//-----------------------------------------------------------------------------
static void* schedule_thread(void* p_arg)
//-----------------------------------------------------------------------------
{
  // schedule loop
  uint64_t startTime = getTimeOfDay() - s_impl->m_simulationTime;
  while(s_impl->m_active)
  {
    s_impl->schedule();
    uint64_t simulationTime = getTimeOfDay() - startTime;
    if(simulationTime < s_impl->m_nextScheduleTime)
    {
      // we have time to sleep
      uint64_t sleepTime = s_impl->m_nextScheduleTime - simulationTime;
      sleepRel(sleepTime);
    }
    else
    {
      // execution of threads took too long
      // TODO: error handling
    }
    s_impl->m_simulationTime = getTimeOfDay() - startTime;
  }
  return NULL;
}

///////////////
// Scheduler //
///////////////

//-----------------------------------------------------------------------------
SCHED::Scheduler::Scheduler(uint32_t p_maxTasks)
//-----------------------------------------------------------------------------
{
  s_instance = this;
  s_impl = new SCHED::SchedulerImpl(p_maxTasks);
}

//-----------------------------------------------------------------------------
SCHED::Scheduler::~Scheduler()
//-----------------------------------------------------------------------------
{
  delete s_impl;
  s_impl = NULL;
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
SCHED::Scheduler* SCHED::Scheduler::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}

//-----------------------------------------------------------------------------
uint32_t SCHED::Scheduler::getMaxTasks() const
//-----------------------------------------------------------------------------
{
  return s_impl->m_maxTasks;
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::start()
//-----------------------------------------------------------------------------
{
  s_impl->m_active = true;
  pthread_create(&(s_impl->m_threadID), NULL, &schedule_thread, NULL);
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::stop()
//-----------------------------------------------------------------------------
{
  s_impl->m_active = false;
  pthread_join(s_impl->m_threadID, NULL);
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::singleStep()
//-----------------------------------------------------------------------------
{
  s_impl->m_simulationTime = s_impl->m_nextScheduleTime;
  s_impl->schedule();
}

//-----------------------------------------------------------------------------
bool SCHED::Scheduler::isActive() const
//-----------------------------------------------------------------------------
{
  return s_impl->m_active;
}

//-----------------------------------------------------------------------------
uint64_t SCHED::Scheduler::getSimulationTime() const
//-----------------------------------------------------------------------------
{
  return s_impl->m_simulationTime;
}

//-----------------------------------------------------------------------------
uint64_t SCHED::Scheduler::getNextScheduleTime() const
//-----------------------------------------------------------------------------
{
  return s_impl->m_nextScheduleTime;
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::setSlowDownFactor(uint32_t p_slowDownFactor)
//-----------------------------------------------------------------------------
{
  if(p_slowDownFactor == 0)
  {
    s_impl->m_slowDownFactor = 1;
  }
  else
  {
    s_impl->m_slowDownFactor = p_slowDownFactor;
  }
}

//-----------------------------------------------------------------------------
uint32_t SCHED::Scheduler::getSlowDownFactor() const
//-----------------------------------------------------------------------------
{
  return s_impl->m_slowDownFactor;
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::registerTask(SCHED::Task* p_task,
                                    uint32_t p_position,
                                    uint32_t p_taskCycle,
                                    uint32_t p_startDelay)
//-----------------------------------------------------------------------------
{
  if(p_position < s_impl->m_maxTasks)
  {
    TaskEntry& taskEntry = s_impl->m_tasks[p_position];
    taskEntry.m_task = p_task;
    taskEntry.m_taskCycle = p_taskCycle;
    taskEntry.m_startDelay = p_startDelay;
    taskEntry.m_nextExecTime = s_impl->m_simulationTime + p_startDelay;
    // the next schedule time is the earliest next execute time
    if(taskEntry.m_nextExecTime < s_impl->m_nextScheduleTime)
    {
      s_impl->m_nextScheduleTime = taskEntry.m_nextExecTime;
    }
  }
}

//-----------------------------------------------------------------------------
void SCHED::Scheduler::unregisterTask(SCHED::Task* p_task)
//-----------------------------------------------------------------------------
{
  for(uint32_t i = 0; i < s_impl->m_maxTasks; i++)
  {
    TaskEntry& taskEntry = s_impl->m_tasks[i];
    if(taskEntry.m_task != NULL)
    {
      taskEntry.m_task = NULL;
      taskEntry.m_taskCycle = 0;
      taskEntry.m_startDelay = 0;
      taskEntry.m_nextExecTime = 0;
      break;
    }
  }
}

