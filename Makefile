SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

septic: $(OBJ)
	gcc -o septic $^ raylib/lib/libraylib.a -lm

%.o: %.c
	gcc -o $@ -c $< -Iraylib/include

run: septic
	./septic
