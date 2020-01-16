This program contains two scripts, a chat client written in C and a chat server written in python.

1. Open UNIX shell with Python interpreter installed and run the server script
```
python chatserve.py PORTNUMBER
``` 

2. Open a different UNIX shell and compile the client C program using
```
make chatclient
```
3. Then to connect a client to the server use the command
```
chatclient HOSTNAME PORTNUMBER
```
where HOSTNAME is a hostname, or internet address, of the server machine running chatserve.py
and PORTNUMBER is the same port used for the server machine

4. Enter the handle of your choosing, up to 10 characters long. 

5. Starting with the client, send alternating messages between the two machines. The client must wait for a 
response before sending another message, and vice versa. 

6. At any time, the client or the server may exit the chatroom 
```
\quit
```
    
*NOTE:  The server will continually wait for a new client connection, whereas the client will exit entirely.*
