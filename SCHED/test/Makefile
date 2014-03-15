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

# keep the linking order of the libraries
LIBS = -L../lib -lSCHED \
       -lpthread
LIB_SCHED = ../lib/libSCHED.a
INCLUDES = -I. -I../src

all:	../bin/test_SCHED_Scheduler

clean:
	\rm -f ../bin/test_SCHED_Scheduler
	\rm -f *.o

tst_SCHED_Scheduler: ../bin/test_SCHED_Scheduler
	cd ../bin; ./test_SCHED_Scheduler

../bin/test_SCHED_Scheduler: test_SCHED_Scheduler.o
	${LINK} -otest_SCHED_Scheduler \
	test_SCHED_Scheduler.o \
	${LIBS}
	mv test_SCHED_Scheduler ../bin

test_SCHED_Scheduler.o: test_SCHED_Scheduler.cpp \
	${LIB_SCHED}
	${CPP} -otest_SCHED_Scheduler.o ${INCLUDES} \
	test_SCHED_Scheduler.cpp
