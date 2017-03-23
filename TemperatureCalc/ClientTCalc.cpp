#include <stdio.h>
#include <iostream>
#include <winsock.h>


using namespace std;
#define DLUGOSC_ADRESU 256

#define PRINTERROR(s)	\
 	fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())


void StreamClient(char *szServer, short nPort, char temp[256])
{
     cout << endl << "Datagram client sending to server:" << szServer << endl;
     cout << "on port:  " << nPort << endl;
     LPHOSTENT lpHostEntry;
     lpHostEntry = gethostbyname(szServer);
     if(lpHostEntry == NULL)
     {
                    PRINTERROR("gethostbyname()");
                    return;
     }
     SOCKET theSocket;
     theSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(theSocket == INVALID_SOCKET)
     {
              PRINTERROR("socket()");
              return;
     }

     SOCKADDR_IN saServer;
     saServer.sin_family = AF_INET;
     saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
     saServer.sin_port = htons(nPort);
     int nRet;
     nRet = connect(theSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
     if(nRet == SOCKET_ERROR)
     {
             PRINTERROR("socket()");
             closesocket(theSocket);
             return;
     }

     char szBuf[256];
     //strcpy(szBuf, "temperatura: ");
     memset(szBuf, '\0', sizeof(szBuf));
     strcat(szBuf,  temp);
     //strcat(szBuf,  " [\370C]");
     //strcpy(szBuf, temp);
     //szBuf = (char)*temp;
     nRet = send(theSocket, szBuf, strlen(szBuf), 0);
     if(nRet == SOCKET_ERROR)
     {
             PRINTERROR("socket()");
             closesocket(theSocket);
             return;
     }

     nRet = recv(theSocket, szBuf, sizeof(szBuf), 0);
     if(nRet == SOCKET_ERROR)
     {
             PRINTERROR("socket()");
             closesocket(theSocket);
             return;
     }

     cout << "Data received from the server: " << szBuf << endl;
     closesocket(theSocket);
     return;
}

int main(int argc, char *argv[])
{
    WORD wVersionRequested = MAKEWORD(1,1);
    WSADATA wsaData;
    int nRet;
    short nPort;
    char celsjusz[256];
    char adres_hosta[DLUGOSC_ADRESU];
    cout << "Input the host adress or hostname : ";
    cin.getline(adres_hosta, DLUGOSC_ADRESU);
    cout << "Input Port number: ";
    cin >> nPort;
    cout << "Input temparature in Celsius scale ";
    //cin.getline(celsjusz, 256);
    cin >> celsjusz;
    cout << endl << "We are connecting with Server " << adres_hosta << endl << " on Port " << nPort << endl;
    nRet = WSAStartup(wVersionRequested, &wsaData);
    if(wsaData.wVersion != wVersionRequested)
    {
                        fprintf(stderr, "\n Wrong version\n");
                        return 0;
    }
    StreamClient(adres_hosta, nPort, celsjusz);
    WSACleanup();
    return 0;
}
