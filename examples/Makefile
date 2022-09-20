FORT = /opt/homebrew/bin/gfortran 

RM = /bin/rm																				#Path to rm for systems with $(RM) overridden

INCLUDES = -I../include															#Add include flags
LFLAGS = -L../lib										  							#Library link path. Either relative or absolute 
LIBS = -lconductivities -lopacities	-lstdc++				#Libs to link.
CFLAGS = -g																					#Add flags
CPPFLAGS = -g

DEPS = ../include/conductivities.h ../include/opacities.h
SRCS = FortranExample.f90														#Your files to compile
OBJS = FortranExample.o															#Make object list
MAIN = FortranExample																#Define the executable

#Build and link the executable
$(OBJS):
	$(FORT) $(CFLAGS) $(SRCS) -c -o $(OBJS)
	$(FORT) $(OBJS) -o $(MAIN) $(LFLAGS) $(LIBS)

clean: 
	$(RM) $(MAIN)
	$(RM) $(OBJS)

