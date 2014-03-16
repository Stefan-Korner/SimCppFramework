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
// Global shared memory for all tasks                                         *
//*****************************************************************************
#ifndef SCHED_Memory_hpp
#define SCHED_Memory_hpp

#include <stddef.h>
#include <stdint.h>

namespace SCHED
{
  class Memory
  {
  public:
    // the memory (or a derived class) shall
    // be created and destroyed in main()
    Memory(size_t p_numVariables);
    virtual ~Memory();

    // the memory is a singleton
    static Memory* instance();

    // memory write access
    virtual void setVariable(size_t p_variable, uint32_t p_value);

    // memory read access
    virtual uint32_t getVariable(size_t p_variable) const;

  protected:
    uint32_t* m_variables;
    size_t m_numVariables;

  private:
    Memory();
    Memory(const Memory& p_scheduler);
    const Memory& operator=(const Memory& p_task);

    static Memory* s_instance;
  };
}

#endif
