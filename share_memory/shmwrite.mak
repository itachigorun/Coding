cc = gcc
program = shmwrite
deps = shmdata.h
objects = shmwrite.o  

$(program) : $(objects)
	$(cc) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) -c $< -o $@

.PHONY : clean
clean :
	rm $(objects) $(program)
	