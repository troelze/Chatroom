/* Chat Client
* Programmed by: Tres Oelze
* Description: This is a chat client that connects to a host to communicate via text messages using a socket API
* Course Name: CS 372 - 400
* Last Modified: 2/10/2019
* Sources: Adapted from Eduonix Learning Solutions Socket Tutorial : https://www.youtube.com/watch?v=LtXEMwSG5-8&t=974s
* as well as ShellWave - C Programming in Linux Tutorial #034 Socket Programming : https://www.youtube.com/watch?v=pFLQkmnmD0o
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
    //check for correct number of arguments
    if (argc != 3)
    {
        printf("Restart program with correct number of inputs.\n");
        exit(1);
    }
    // convert string input to integer for port number
    int portnum = atoi(argv[2]);



    //create a socket
    int chat_socket;
    chat_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;    //sets family so it knows what address type
    server_address.sin_port = htons(portnum);   // converts port number to appropriate data format


    //get the hostname information from the second argument passed
    struct hostent *hp;
    hp = gethostbyname(argv[1]);
    //print error if this fails
    if (hp ==0)
    {
        perror("gethostbyname failed");
        exit(1);
    }

    //copy hostname information into server_address 
    memcpy(&server_address.sin_addr, hp->h_addr, hp->h_length);
    
    //connect to server given hostname, port
    int connection_status = connect(chat_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    
    // check for error with the connection
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
        exit(1);

    }

    // define client message and server message as character array capabable of holding 10 letter handle and 500 character message
    char handle[511];
    char temp[511];
    char server_response[511];
    char client_message[511];
    
    //get handle from user
    printf("Enter your handle (max 10 characters): ");
    scanf("%s", temp);
    // read in message from client keyboard
    while ((getchar()) != '\n');
    //printf("Length: %d", strlen(handle));
    
    
    strcat(temp, ">");
    //make a copy of the handle 
    strcpy(handle, temp);

while (1) {

    
    
    printf("%s", handle);
    //get message to be sent to server from client
    fgets(client_message, sizeof(client_message), stdin);

    //if message is not quit, send and receive message
    if (strncmp(client_message, "\\quit", 5) != 0)
    {
        
        //prepend handle to message
        strcat(handle, client_message);
        //char* s = concat(handle, client_message);

        send(chat_socket, handle, sizeof(handle), 0);
        //free(s);
        //receive data from the server
        recv(chat_socket, &server_response, sizeof(server_response), 0);

        //if server quits, end 
        if (strncmp(server_response, "\\quit", 5) == 0)
        {
            printf("The server has logged off. Goodbye!\n");
            return 0;
        }

        // print out the server's response
        printf("server>%s\n", server_response);

        memset(server_response,0,strlen(server_response));
        memset(handle,0,strlen(temp));

    
        strcpy(handle, temp);

    }
    else        //if message is quit, exit the program after sending notice to server
    {
        send(chat_socket, client_message, sizeof(client_message), 0);
        break;
    }


}

    // and then close the socket
    close(chat_socket);
    return 0;
}