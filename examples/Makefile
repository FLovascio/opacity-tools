CC = /usr/bin/clang  																#Path to your C compiler (Preferably the same used to compile opacity-tools)
CPP = /usr/bin/clang++															#Path to your C++ compiler (Preferably the same used to compile opacity-tools)

RM = /bin/rm																				#Path to rm for systems with $(RM) overridden

INCLUDES = -I../include															#Add include flags
LFLAGS = -L../lib										  							#Library link path. Either relative or absolute 
LIBS = -lconductivities -lopacities									#Libs to link.
CFLAGS = -g -std=c17																#Add flags
CPPFLAGS = -g

DEPS = ../include/conductivities.h ../include/opacities.h
SRCS = CExample.c																		#Your files to compile
OBJS = CExample.o   																#Make object list
MAIN = CExample																			#Define the executable

#Build and link the executable
$(OBJS):
	$(CC) $(CFLAGS) $(SRCS) -c -o $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(MAIN) $(LFLAGS) $(LIBS)

clean: 
	$(RM) *.o $(MAIN)

