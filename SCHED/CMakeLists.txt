#******************************************************************************
# (C) 2014, Stefan Korner, Austria                                            *
#                                                                             *
# The Sim C++ Framework is free software; you can redistribute it and/or      *
# modify it under the terms of the GNU Lesser General Public License as       *
# published by the Free Software Foundation; either version 2.1 of the        *
# License, or (at your option) any later version.                             *
#                                                                             *
# The Sim C++ Framework is distributed in the hope that it will be useful,    *
# but WITHOUT ANY WARRANTY; without even the implied warranty of              *
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser     *
# General Public License for more details.                                    *
#******************************************************************************
# cmake configuration file                                                    *
#******************************************************************************

include_directories(src)

add_library(SCHED
  src/SCHED_Memory.cpp
  src/SCHED_Scheduler.cpp)
target_link_libraries(SCHED)

add_executable(test_SCHED_Memory
  test/test_SCHED_Memory.cpp)
target_link_libraries(test_SCHED_Memory
  SCHED
  pthread)

add_executable(test_SCHED_Scheduler
  test/test_SCHED_Scheduler.cpp)
target_link_libraries(test_SCHED_Scheduler
  SCHED
  pthread)

if(SimCppFramework_build_tests)
  include_directories(../3rdparty/gtest/include)

  add_executable(test_SCHED_gtest_example
    test/test_SCHED_gtest_example.cpp)
  target_link_libraries(test_SCHED_gtest_example
    gtest
    gtest_main)
  add_test(NAME test_SCHED_gtest_example
    COMMAND test_SCHED_gtest_example)
endif()

