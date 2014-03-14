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

LIB_SCHED = ../lib/libSCHED.a
INCLUDES = -I.

all: ${LIB_SCHED}

clean:
	\rm -f ../lib/libSCHED.so ../lib/libSCHED.a *.o

../lib/libSCHED.so: \
	SCHED_Scheduler.o
	${LIB_DYNAMIC} -olibSCHED.so \
	SCHED_Scheduler.o
	mv libSCHED.so ../lib

../lib/libSCHED.a: \
	SCHED_Scheduler.o
	${LIB_STATIC} libSCHED.a \
	SCHED_Scheduler.o
	mv libSCHED.a ../lib

SCHED_Scheduler.o: SCHED_Scheduler.cpp \
	SCHED_Scheduler.hpp
	${CPP} -oSCHED_Scheduler.o ${INCLUDES} \
	SCHED_Scheduler.cpp
