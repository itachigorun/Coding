cc = gcc
program = msgqueue
deps = head.h
objects = msgsend.o  

$(program) : $(objects)
	$(cc) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) -c $< -o $@

.PHONY : clean
clean :
	rm $(objects) $(program)
	