### Simple Make File
### Author: Tres Oelze
### Date: 2/19/2019 

chatclient: chatclient.o
	gcc chatclient.o -o chatclient

chatclient.o: chatclient.c
	gcc -c chatclient.c

clean:
	rm *.o chatclient
