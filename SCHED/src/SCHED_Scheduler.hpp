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
#ifndef SCHED_Scheduler_hpp
#define SCHED_Scheduler_hpp

#include <stddef.h>
#include <stdint.h>

namespace SCHED
{
  static const uint32_t MAX_TASKS = 16;

  //---------------------------------------------------------------------------
  class Task
  //---------------------------------------------------------------------------
  {
  public:
    // p_position defines the rank in the task list,
    //            allowed values are: 0...(MAX_TASKS - 1)
    // p_taskCycle and p_startDelay are in micro-seconds
    Task(uint32_t p_position, uint32_t p_taskCycle, uint32_t p_startDelay = 0);
    virtual ~Task();
    virtual void exec(uint64_t p_simulationTime) = 0;

  private:
    Task();
    Task(const Task& p_task);
    const Task& operator=(const Task& p_task);
  };

  class SchedulerImpl;

  //---------------------------------------------------------------------------
  class Scheduler
  //---------------------------------------------------------------------------
  {
  public:
    friend class Task;

    // the scheduler (or a derived class) shall
    // be created and destroyed in main()
    Scheduler();
    virtual ~Scheduler();

    // the scheduler is a singleton
    static Scheduler* instance();

    // activates the scheduler as background thread
    virtual void start();

    // deactivates the scheduler
    virtual void stop();

    // deactivates the scheduler
    virtual void singleStep();

    // indicates if the scheduler is active
    virtual bool isActive() const;

    // provide the simulation time (starts with 0)
    virtual uint64_t getSimulationTime() const;

    // provide the next schedule time
    virtual uint64_t getNextScheduleTime() const;

    // allows to slow down the scheduling for debugging purpose,
    // the slow down factor should be >= 1
    virtual void setSlowDownFactor(uint32_t p_slowDownFactor);

    // provide the slow down factor (default = 1)
    virtual uint32_t getSlowDownFactor() const;

  protected:
    // a task registers itself automatically with this method
    virtual void registerTask(Task* p_task,
                              uint32_t p_position,
                              uint32_t p_taskCycle,
                              uint32_t p_startDelay);

    // removes a task from the schedule plan,
    // the task is not owned (memory managed) by the scheduler
    // and must be deleted after unregistration by the caller
    virtual void unregisterTask(Task* p_task);

  private:
    Scheduler(const Scheduler& p_scheduler);
    const Scheduler& operator=(const Scheduler& p_task);

    static Scheduler* s_instance;
  };
}

#endif
