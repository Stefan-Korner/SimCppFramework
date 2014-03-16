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
#include "SCHED_Memory.hpp"

#include <string.h>

// global variables
SCHED::Memory* SCHED::Memory::s_instance = NULL;

//-----------------------------------------------------------------------------
SCHED::Memory::Memory(size_t p_numVariables):
  m_variables(NULL), m_numVariables(p_numVariables)
//-----------------------------------------------------------------------------
{
  m_variables = new uint32_t[p_numVariables];
  memset(m_variables, 0, p_numVariables * sizeof(uint32_t));
  s_instance = this;
}

//-----------------------------------------------------------------------------
SCHED::Memory::~Memory()
//-----------------------------------------------------------------------------
{
  delete[] m_variables;
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
SCHED::Memory* SCHED::Memory::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}

//-----------------------------------------------------------------------------
void SCHED::Memory::setVariable(size_t p_variable, uint32_t p_value)
//-----------------------------------------------------------------------------
{
  if(p_variable < m_numVariables)
  {
    m_variables[p_variable] = p_value;
  }
}

//-----------------------------------------------------------------------------
uint32_t SCHED::Memory::getVariable(size_t p_variable) const
//-----------------------------------------------------------------------------
{
  if(p_variable < m_numVariables)
  {
    return m_variables[p_variable];
  }
  return 0;
}

//-----------------------------------------------------------------------------
size_t SCHED::Memory::getNumVariables() const
//-----------------------------------------------------------------------------
{
  return m_numVariables;
}
