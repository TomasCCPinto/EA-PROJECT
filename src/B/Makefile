CC = g++
FLAGS = -Wall -Wextra -O2

OBJ = main.o
PROG = prog
INPUT = inputEnun.txt



run:	comp


comp:	${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${PROG}
	./${PROG} < ${INPUT}

clean:	
	rm ${OBJ} ${PROG}


%.o:	%.c
	${CC} ${FLAGS} ^$
