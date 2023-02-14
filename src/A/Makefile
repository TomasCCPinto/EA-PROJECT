CC = g++
FLAGS = -Wall -Wextra

OBJ = A.o
PROG = prog
INPUT = input.txt



run:	comp


comp:	${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${PROG}
	./${PROG} < ${INPUT}

clean:	${OBJ}
	rm ${OBJ} ${PROG}


%.o:	%.c
	${CC} ${FLAGS} ^$
