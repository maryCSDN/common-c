main : main.o
	gcc main.o -o main
main.o : src/com_log.c
	gcc ./src/com_log.c -c -o main.o
	
clean:
	del *.o main.exe -rf
	
	