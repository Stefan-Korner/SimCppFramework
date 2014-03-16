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
// Memory - Unit Tests                                                        *
//*****************************************************************************
#include "SCHED_Memory.hpp"

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
void dumpMemory()
//-----------------------------------------------------------------------------
{
  cout << "--- memory ---" << endl;
  for(size_t i = 0; i < NUM_VARS; i++)
  {
    cout << "memory[" << i << "] = " << GET_VAR(i) << endl;
  }
}
//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  SCHED::Memory memory(10);
  dumpMemory();
  SET_VAR(0, 1234);
  SET_VAR(5, 5678);
  SET_VAR(10, 1010);
  dumpMemory();
  return 0;
}
