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
	/*
	int serv_socket, newsocket, port_no;
	struct sockaddr_in server_addr, cli_addr;
	socklen_t clilen;
	serv_socket = socket(AF_INET, SOCK_STREAM, 0);
	port_no = 2301;//enter port ID
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port_no); //port_no
	bzero((char *) &server_addr, sizeof(server_addr));
	bind(serv_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
	listen(serv_socket, 5);
	clilen = sizeof(cli_addr);
    newsocket = accept(serv_socket, (struct sockaddr *) &cli_addr, &clilen);
	return 0;*/

///////////

	map <string, string> user_data;

	string input;
	cout<< "Enter a file name: ";
	getline(cin, input);
	ifstream input_file;
	input_file.open(input.c_str());
    
	string id, p_key;

	while(!input_file.eof()){
		getline(input_file, input);
		stringstream ss(input);
		ss >> id >> p_key;
		user_data[id] = p_key;//input id and key into dictionary
	}

	int port_no = 0;
	cout<< "Enter server port numnber: ";
	getline(cin, input);
    port_no = atoi(input.c_str());


///////////
	int listenfd = 0;
	
    struct sockaddr_in serv_addr; 

    char sendBuff[256] = "";
    string send;
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port_no); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    string term = "Terminate";
    listen(listenfd, 10); 
	int connfd = 0;
	int read_size = 0;
    //cout<<"before loop"<< endl;
    while(true)
    {
            connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
            
            bzero(sendBuff, 256);
    		read_size = read(connfd, sendBuff, 256);
            if(sendBuff == term){
                //cout<< "Im dying!!!!";
                close(connfd);
                exit(1);
            }
    		//if(read_size == 0)
    			//break;
            //if(sendBuff == "Terminate")
              //  exit(1);
        	//connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        	//cout<< "socket accept"<<endl;
        	//ticks = time(NULL);//time stuff????
        	//snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));

            string sB = user_data[sendBuff];
            

            write(connfd,sB.c_str(), 256);
            //const char *sendBack;
            //sendBack = sB.c_str();
            //cout<<"socket write"<< sendBack;
        	//write(connfd, sendBack, strlen(sendBack)); 

        	close(connfd);
            sleep(1);
		
        //terminate user request will force porces to terminate/ exit
     }
}
/*

void do_something(int s, map<string, string> grades) {
	char buffer[256] = "";
	string grade = "";

	cout<<"Received a connection."<<endl;

	int bytesRead = read(s, buffer, 256);
	
	string name = (string)buffer;
	cout<<"Data("<<bytesRead<<"): "<<buffer<<endl;
	
	if (grades.find(buffer) != grades.end()) {
		grade = grades[buffer];
	} else {
		srand(time(NULL));
		grade = to_string(rand() % 55 + 45);
	}
	cout<<"Grade: "<<grade<<endl;
	
	write(s, grade.c_str(), 256);




	////////
	queue <string> q;
	string input;
	while(getline(cin, input))
		
int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}









	}
}


    #define BACKLOG 20
    //#define DEST_IP "127.0.0.1"


   
    	cout<< "Enter a file name: ";
    	getline(cin, input);

    	//Read in file name of user ids and keys
    	//store data into a table


    	cout<< "Enter server port number: ";

    	//create stream socket
    	//bind to specified port number
    	//do a listen() to specify number of maximum number of connection requests
		//accept() waits for connection requests
		//reads in string contianing ID
		//send back public key
		//terminate will force process to end



        ssize_t size =0;
        char buffer[1024];

        for( ; ; )
        {
            size = read(s,buffer,1024);
            if(size == 0)
            {
                return 0;
            }
        }
        sprintf(buffer, "%d bytes altogether\n", (int)size);
        write(s, buffer,strlen(buffer)+1);



        return 0;
    }

    int main(int argc,char *argv[])
    {
        //cout<<"?";
        int ss, sc, r, err;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int   opt=1; 
        pid_t pid;

        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(PORT);

        ss = socket(AF_INET, SOCK_STREAM, 0);
        if(ss<0)
        {
            cout<<"[process infro]socket error"<<endl;
            return -1;
        }
        cout<<"[process infro]socket successful"<<endl;

        r = setsockopt(ss, SOL_SOCKET,SO_REUSEADDR, (void*)&opt,sizeof(opt));
        if (r == -1)
        { 
            perror("setsockopt(listen)"); 
            return 0;
        }
        cout<<"[process infro]sockopt successful"<<endl;

        cout<<"?";
        err = bind(ss, (struct sockaddr*) &server_addr, sizeof( server_addr));
        cout<<"err";
        if(err < 0)
        {
            cout<<"[process infro]bind error"<<endl;
            return -1;
        }
        cout<<"[process infro]bind successful";


        err=listen(ss, BACKLOG);
        if(err <0)
        {
            cout<<"[process infro]listen error"<<endl;
            return -1;
        }
        cout<<"[process infro]lisen successful";

        for( ; ; )
        {
            int addrlen = sizeof(struct sockaddr);

            sc = accept(ss, (struct sockaddr*)&client_addr, (socklen_t *)&addrlen);

            if(sc < 0)
            {
                continue;
            }

            pid =  fork();
            if (pid == 0)
            {
                close(ss);
                process_conn_server(sc);
            }
            else
            {
                close(sc);
            }
        }
        //opt=0; 

        //setsockopt(ss,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(len));*/
    