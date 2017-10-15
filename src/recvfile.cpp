/*
    Simple udp server
*/
#include <iostream>
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;
 
//#define BUFLEN 256  //Max length of buffer
//#define PORT 8000   //The port on which to listen for incoming data
 
/* arguments: filename windowsize buffersize port */
int main(int argc, char ** argv)
{
    struct sockaddr_in si_me, si_other;
     
    int s, i, recv_len;
    socklen_t slen = sizeof(si_other);
    char *filename;
    int windowSize;
    int buffersize;
    int destinationPort;
    if(argc != 5){
        cout << "./recvfile filename windowsize buffersize port" << endl;
        exit(0);
    } else {
        filename = argv[1];
        windowSize = atoi(argv[2]);
        buffersize = atoi(argv[3]);
        destinationPort = atoi(argv[4]);
    }

    //akan dipake buat framenya
    char *buf = new char[buffersize];
     
    //create a UDP socket
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(destinationPort);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    int con = bind(s , (struct sockaddr*)&si_me, sizeof(si_me));
     
    //keep listening for data
    while(1)
    {
        cout << "Waiting for data..." << endl;
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        recv_len = recvfrom(s, buf, buffersize, 0, (struct sockaddr *) &si_other, &slen);
         
        //print details of the client/peer and the data received
        cout << "Received packet from " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << endl;
        cout << "Data: " << buf << endl;
         
        //now reply the client with the same data
        sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen);
        
    }
 
    //TODO: klo kirim ada asci spasi blom bisa
    return 0;
}