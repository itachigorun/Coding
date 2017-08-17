cc = gcc
program = shmread
deps = shmdata.h
objects = shmread.o  

$(program) : $(objects)
	$(cc) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) -c $< -o $@

.PHONY : clean
clean :
	rm $(objects) $(program)
	