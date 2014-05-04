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
# Makefile                                                                    *
#******************************************************************************
include ../../Makefile.include

GTEST_DIR = ../../3rdparty/gtest
GTEST_INCLUDE = -I${GTEST_DIR}/include
GTEST_LIB_DIR = ${GTEST_DIR}/lib

# keep the linking order of the libraries
LIBS = -L../lib -lSCHED \
       -lpthread
LIB_SCHED = ../lib/libSCHED.a
INCLUDES = -I. -I../src

all:	../bin/test_SCHED_Memory \
	../bin/test_SCHED_Scheduler \
	../bin/test_SCHED_gtest_example

clean:
	\rm -f ../bin/test_SCHED_Memory
	\rm -f ../bin/test_SCHED_Scheduler
	\rm -f ../bin/test_SCHED_gtest_example
	\rm -f *.o

tst_SCHED_Memory: ../bin/test_SCHED_Memory
	cd ../bin; ./test_SCHED_Memory

tst_SCHED_Scheduler: ../bin/test_SCHED_Scheduler
	cd ../bin; ./test_SCHED_Scheduler

tst_SCHED_gtest_example: ../bin/test_SCHED_gtest_example
	cd ../bin; ./test_SCHED_gtest_example

../bin/test_SCHED_Memory: test_SCHED_Memory.o
	${LINK} -otest_SCHED_Memory \
	test_SCHED_Memory.o \
	${LIBS}
	mv test_SCHED_Memory ../bin

../bin/test_SCHED_Scheduler: test_SCHED_Scheduler.o
	${LINK} -otest_SCHED_Scheduler \
	test_SCHED_Scheduler.o \
	${LIBS}
	mv test_SCHED_Scheduler ../bin

../bin/test_SCHED_gtest_example: test_SCHED_gtest_example.o
	${LINK} -otest_SCHED_gtest_example \
	test_SCHED_gtest_example.o \
	-L${GTEST_LIB_DIR} -lgtest_main -lpthread
	mv test_SCHED_gtest_example ../bin

test_SCHED_Memory.o: test_SCHED_Memory.cpp \
	${LIB_SCHED}
	${CPP} -otest_SCHED_Memory.o ${INCLUDES} \
	test_SCHED_Memory.cpp

test_SCHED_Scheduler.o: test_SCHED_Scheduler.cpp \
	${LIB_SCHED}
	${CPP} -otest_SCHED_Scheduler.o ${INCLUDES} \
	test_SCHED_Scheduler.cpp

test_SCHED_gtest_example.o: test_SCHED_gtest_example.cpp \
	${GTEST_LIB_DIR}/libgtest_main.a
	${CPP} -otest_SCHED_gtest_example.o ${GTEST_INCLUDE} \
	test_SCHED_gtest_example.cpp
