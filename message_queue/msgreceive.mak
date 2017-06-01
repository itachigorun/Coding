cc = gcc
program = msgreceive
deps = head.h
objects = msgreceive.o  

$(program) : $(objects)
	$(cc) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) -c $< -o $@

.PHONY : clean
clean :
	rm $(objects) $(program)
	