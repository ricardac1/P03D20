all: main clean

main: graph charstack doublestack check_exp
	gcc graph.o charstack.o check_exp.o doublestack.o -o ../build/graph

graph:
	gcc -Wall -Wextra -Werror -c graph.c

charstack:  
	gcc -Wall -Wextra -Werror -c charstack.c

doublestack: 
	gcc -Wall -Wextra -Werror -c doublestack.c 

check_exp:
	gcc -Wall -Wextra -Werror -c check_exp.c

clean:
	rm -f *.o 