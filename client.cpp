//Joyce Shaheen
//COSC 3360 Spring 2017
//PSID: 1244818
//
#include <iostream>
#include <map>
#include <istream>
#include <fstream>
#include <string.h>
#include <fstream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <sstream>
#include <cstdio>
#include <string.h>
using namespace std;


int main (){
	string hostname;
    string p;
    char buffer[256]= "";
    string send;
    char inbuff[256];
	int port_no, sockfd;
	struct sockaddr_in serv_addr;
	while(true){
		cout<< "Enter a server host name: ";
		getline(cin, hostname);
		if((hostname == "program.cs.uh.edu") || (hostname == "localhost"))
			break;
		else
			cout<< "Host not recognized\n";
	}

	cout<< "Enter server port number: ";
	getline(cin, p);
    port_no = atoi(p.c_str());

    int n;
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
        cout<<"ERROR opening socket";

    memset(&serv_addr, 0,  sizeof(serv_addr));//
    serv_addr.sin_family = AF_INET;
    
    //bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    
    serv_addr.sin_port = htons(port_no);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        cout<<"ERROR connecting";

    printf("Please enter a user name: ");
    string b;
    cin.getline(buffer, 256, '\n');
    b = (string)buffer;
    if(b == "Terminate"){
        write(sockfd,buffer,strlen(buffer));
        close(sockfd);
        exit(1);
    }

    
    //buffer = b.c_str(); 
    //bzero(buffer, 20);
    //fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));//////////////
    //cout<< buffer<< endl;
    if (n < 0) 
         cout<<"ERROR writing to socket";
    bzero(buffer,256);
    n = read(sockfd, inbuff ,256);///////////////////////
    //cout<< "socket read" << inbuff << endl;
    if (n < 0) 
         cout<<"ERROR reading from socket";
    //cout<< inbuff<< "   " <<*inbuff<<endl;
    cout<< "The public key for user " << b << " is " << inbuff <<endl;
    close(sockfd);
    
    return 0;


}