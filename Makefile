main: main.o manipulatefile.o
	gcc main.o manipulatefile.o -o main -lncurses

main.o: main.c
	gcc -c main.c

manipulatefile.o: src/manipulatefile.c header/manipulatefile.h
	gcc -c src/manipulatefile.c


#Dependecias para openfile.c
openfile: openfile.o manipulatefile.o
	gcc openfile.o manipulatefile.o -o openfile -lncurses

openfile.o: openfile.c
	gcc -c openfile.c


#Dependecias para createfile.c
createfile: createfile.o manipulatefile.o
	gcc createfile.o manipulatefile.o -o createfile -lncurses

createfile.o: createfile.c
	gcc -c createfile.c



#Limpar arquivos .o
clean:
	rm *.o
	rm main createfile openfile compilefile 
