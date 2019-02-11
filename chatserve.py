# Chat Server
# Programmed by: Tres Oelze
# Description: This is a chat server that waits for a client request to respond with text messages via a socket API
# Course Name: CS 372 - 400
# Last Modified: 2/10/2019
# Adapted from CS 372  - Lecture 15 - Socket programming, slide "Example Application: TCP server"


# import socket library API
from socket import *
import sys

# validate single port number was provided
if (len(sys.argv) != 2) : 
    print 'Wrong number of arguments'
    

else :
    if (sys.argv[1].isdigit()) :            #validate port number is integer value
        serverPort = int(sys.argv[1])       




        serverSocket = socket(AF_INET,SOCK_STREAM)      # initiate socket connection
        serverSocket.bind(('',serverPort))
        serverSocket.listen(1)
        print 'The server is ready to chat'


        
        while 1: 
            connectionSocket, addr = serverSocket.accept()  # wait for client to connect
        
            print 'client connected...'

            while 1:  
                client_message = connectionSocket.recv(1024)    

                if '\quit' not in client_message:               # once connected, print client message and send server message 
                    left = client_message.partition("\n")[0]
                    print (left)
                    server_response = raw_input('server>')
                       
                    connectionSocket.send(server_response)      
                    if '\quit' in server_response:          # if server message is quit, exit the script
                        print 'client disconnected.'
                        break
                else:                                           # if client quits, print message and wait for new client
                    print 'client disconnected.'
                    break

        connectionSocket.close() 

    else : 
        print 'Invalid Port Number'
    