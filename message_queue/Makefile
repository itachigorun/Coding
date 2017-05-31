cc = gcc
program = msgqueue
deps = head.h
objects = msgreceive.o msgsend.o 

$(program) : $(objects)
	$(cc) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) -c $(objects)

.PHONY : clean
clean :
	rm $(objects) $(program)
	