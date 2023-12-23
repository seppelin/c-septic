SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.Phony: clean

septic: $(OBJ)
	gcc -o septic $^ raylib/lib/libraylib.a -lm

%.o: %.c
	gcc -o $@ -c $< -Iraylib/include

run: septic
	./septic

clean:
	rm -rf septic $(OBJ)
