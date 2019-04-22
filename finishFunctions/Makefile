PROGRAMS = p5

OBJECTS = danielFunctions.o emmanuelleFunctions.o vedikaFunctions.o cs2123p5Driver.o

INCLUDES = cs2123p5.h

all: $(PROGRAMS)

clean:
	rm -f $(OBJECTS) $(PROGRAMS)

run:
	./p5 < p5Input.txt


# make for executable
p5: ${OBJECTS}
	gcc -g -o p5 ${OBJECTS}

# simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c $<

