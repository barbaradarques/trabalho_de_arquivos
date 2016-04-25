
all:
	gcc -o ./build/trabalho src/*.c -I./includes
run:
	./build/trabalho < entrada.txt
val:
	gcc -o trabalho src/*.c -I./includes -g -O0 < entrada.txt
	valgrind --leak-check=yes ./trabalho 
