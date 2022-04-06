CC			= c++
FLAGS		=
CFLAGS		= -g -O2 -Wno-write-strings -Wno-cpp -w -lm

OBJ_FILE	= main.o lifxLAN.o
EXE_FILE	= lifxlan


${EXE_FILE}: ${OBJ_FILE}
	${CC} ${FLAGS} -o ${EXE_FILE} ${OBJ_FILE}

main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp

lifxLAN.o: lifxLAN.cpp
	${CC} ${CFLAGS} -c lifxLAN.cpp

clean:
	rm -f ${OBJ_FILE} ${EXE_FILE}

