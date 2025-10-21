# Programarea Calculatoarelor, seria CC
# Tema2 - 2048

build: 2048

2048: 2048.c
	gcc -Wall 2048.c -o 2048 -lcurses

clean:
	rm -f 2048

pack:
	zip -FSr 312CC_Manda_Stefan.zip README Makefile *.c *.h

run:
	./2048

.PHONY: pack clean
