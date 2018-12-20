#include <iostream>
#include <string>
#include <stdlib.h>
#include <winsock.h>//dont forget to add wsock32.lib to linker dependencies
#include <sstream>

using namespace std;

#define BUFFERSIZE 1024
void die_with_error(char *errorMessage);
void die_with_wserror(char *errorMessage);
string IntToString(int);

int main(int argc, char *argv[])
{
string sensorData = "<root>";
        for(int i=0;i=1;i++)
    {
        sensorData += "<reading><time>10:00</time><temperature>30</temperature></reading><reading><time>11:10</time><temperature>35</temperature></reading><reading><time>12:30</time><temperature>30</temperature></reading><reading><time>1:30</time><temperature>25</temperature></reading><reading><time>2:00</time><temperature>50</temperature></reading><reading><time>3:20</time><temperature>40</temperature></reading><reading><time>4:40</time><temperature>17</temperature></reading><reading><time>6:00</time><temperature>20</temperature></reading><reading><time>7:00</time><temperature>43</temperature></reading><reading><time>9:50</time><temperature>14</temperature></reading><reading><time>9:55</time><temperature>40</temperature></reading>";
    }
    sensorData += "</root>";
    string request;
    string response;
    int resp_leng;

    char buffer[BUFFERSIZE];
    struct sockaddr_in serveraddr;
    int sock;

    WSADATA wsaData;
    char *ipaddress = "127.0.0.1";
    int port = 8080;
    string sensorDataLengthStr = IntToString(sensorData.length());

    request+="POST /sendreading HTTP/1.0\r\n"; // request+="GET /test.html HTTP/1.0\r\n";
    request+="Host: localhost\r\n";
    request+="Content-Length: " + sensorDataLengthStr + "\r\n";
    request+="Accept-Charset: utf-8\r\n";
    request+="\r\n";

    while(1)
    {
        //init winsock
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            die_with_wserror("WSAStartup() failed");

        //open socket
        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            die_with_wserror("socket() failed");

        //connect
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family      = AF_INET;
        serveraddr.sin_addr.s_addr = inet_addr(ipaddress);
        serveraddr.sin_port        = htons((unsigned short) port);
        if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
            die_with_wserror("connect() failed");

        //send request
        if (send(sock, request.c_str(), request.length(), 0) != request.length())
            die_with_wserror("send() sent a different number of bytes than expected");
        //Send Sensor Reading
        if (send(sock, sensorData.c_str(), sensorData.length(), 0) != sensorData.length())
            die_with_wserror("send() sent a different number of bytes than expected");

        //get response
        response = "";
        resp_leng= BUFFERSIZE;
        while (resp_leng == BUFFERSIZE)
        {
            resp_leng= recv(sock, (char*)&buffer, BUFFERSIZE, 0);
            if (resp_leng>0)
                response+= string(buffer).substr(0,resp_leng);
            //note: download lag is not handled in this code
        }

        //display response
        cout << response << endl;

        //disconnect
        closesocket(sock);

        //cleanup
        WSACleanup();
        cout << "going to sleep\n";
        Sleep(3000);
        cout << "waking up!!\n";
    }
    return 0;
}

void die_with_error(char *errorMessage)
{
    cerr << errorMessage << endl;
    exit(1);
}

void die_with_wserror(char *errorMessage)
{
    cerr << errorMessage << ": " << WSAGetLastError() << endl;
    exit(1);
}

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}
