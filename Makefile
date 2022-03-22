CC			= gcc
FLAGS		= -lm

OBJ_FILE	= lifxLAN.o message.o util.o setters.o getters.o
EXE_FILE	= lifxlan

${EXE_FILE}: ${FLAGS} ${OBJ_FILE}
	${CC} ${FLAGS} -o ${EXE_FILE} ${OBJ_FILE}

lifxLAN.o: lifxLAN.c
	${CC} -c lifxLAN.c

messageMaker.o: message.c
	${CC} -c messageMaker.c

util.o: util.c
	${CC} -c util.c

setters.o: setters.c
	${CC} -c setters.c

getters.o: getters.c
	${CC} -c getters.c

clean:
	rm -f ${OBJ_FILE} ${EXE_FILE}
