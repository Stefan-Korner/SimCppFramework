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
  class Task
  {
  public:
    // p_taskCycle and p_startDelay are in milli-seconds
    Task(uint32_t p_taskCycle, uint32_t p_startDelay);
    virtual ~Task();
    virtual bool exec() = 0;

  private:
    Task();
    Task(const Task& p_task);
    const Task& operator=(const Task& p_task);
  };

  class Scheduler
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

    // indicates if the scheduler is active
    virtual bool isActive() const;

  protected:
    // a Task registers itself automatically with this method
    virtual void registerTask(Task* p_task,
                              uint32_t p_taskCycle,
                              uint32_t p_startDelay);

    // removes a Task from the schedule plan
    virtual void unregisterTask(Task* p_task);

    bool m_active;

  private:
    Scheduler(const Scheduler& p_scheduler);
    const Scheduler& operator=(const Scheduler& p_task);

    static Scheduler* s_instance;
  };
}

#endif
