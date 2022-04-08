CS105: employee.o project.o CS105.o
	gcc -o CS105 employee.o project.o CS105.o
CS105.o : CS105.c CS105.h
	gcc -c CS105.c
project.o: project.c project.h
	gcc -c project.c
employee.o : employee.c employee.h
	gcc -c employee.c