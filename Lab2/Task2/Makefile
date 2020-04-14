all: build run clean
NAME_PART = Add
PATH_LIB = C:/BSUIR/C/C89Labs

build:
	cd $(CURDIR)
	gcc -std=c89 -c $(PATH_LIB)/deRigorich/deRigorich.c -o deRigorich.o
	ar rcs libdeRigorich.a deRigorich.o
	gcc -std=c89 -I $(PATH_LIB)/deRigorich -c "$(NAME_PART).c" -o "$(NAME_PART).o"
	gcc -std=c89 "$(NAME_PART).o" -L . -l deRigorich -o "$(NAME_PART).exe"

run:
	./$(NAME_PART)

clean:
	git clean -x -f