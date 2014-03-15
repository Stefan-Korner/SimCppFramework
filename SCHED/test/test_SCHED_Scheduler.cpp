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
// Scheduler - Unit Tests                                                     *
//*****************************************************************************
#include "SCHED_Scheduler.hpp"

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
class Task0: public SCHED::Task
//-----------------------------------------------------------------------------
{
public:
  Task0(): SCHED::Task(0, 100) {}
  virtual ~Task0() {}
  virtual void exec(uint64_t p_simulationTime)
  {
    cout << "Task0::exec(" << p_simulationTime << ")" << endl;
  }
};

//-----------------------------------------------------------------------------
class Task1: public SCHED::Task
//-----------------------------------------------------------------------------
{
public:
  Task1(): SCHED::Task(1, 200) {}
  virtual ~Task1() {}
  virtual void exec(uint64_t p_simulationTime)
  {
    cout << "Task1::exec(" << p_simulationTime << ")" << endl;
  }
};

//-----------------------------------------------------------------------------
class Task2: public SCHED::Task
//-----------------------------------------------------------------------------
{
public:
  Task2(): SCHED::Task(2, 200, 100) {}
  virtual ~Task2() {}
  virtual void exec(uint64_t p_simulationTime)
  {
    cout << "Task2::exec(" << p_simulationTime << ")" << endl;
  }
};

//-----------------------------------------------------------------------------
class Task3: public SCHED::Task
//-----------------------------------------------------------------------------
{
public:
  Task3(): SCHED::Task(3, 50) {}
  virtual ~Task3() {}
  virtual void exec(uint64_t p_simulationTime)
  {
    cout << "Task3::exec(" << p_simulationTime << ")" << endl;
  }
};

//-----------------------------------------------------------------------------
class Task4: public SCHED::Task
//-----------------------------------------------------------------------------
{
public:
  Task4(): SCHED::Task(4, 100) {}
  virtual ~Task4() {}
  virtual void exec(uint64_t p_simulationTime)
  {
    cout << "Task4::exec(" << p_simulationTime << ")" << endl;
  }
};

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  SCHED::Scheduler scheduler;
  new Task0;
  new Task1;
  new Task2;
  new Task3;
  new Task4;
  cout << "---singleStep---" << endl;
  SCHED::Scheduler::instance()->singleStep();
  cout << "---singleStep---" << endl;
  SCHED::Scheduler::instance()->singleStep();
  cout << "---singleStep---" << endl;
  SCHED::Scheduler::instance()->singleStep();
  cout << "---singleStep---" << endl;
  SCHED::Scheduler::instance()->singleStep();
  cout << "---singleStep---" << endl;
  SCHED::Scheduler::instance()->singleStep();
  return 0;
}
