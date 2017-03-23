#include <stdio.h>
#include <iostream>
#include <winsock.h>


using namespace std;
#define DLUGOSC_ADRESU 256

#define PRINTERROR(s)	\
 	fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

char SetCelsius()
{
    char celsius[256];
    cout << "Input temperature in Celsius scale ";
    cin >> celsius;

    return celsius[256];
}


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
     memset(szBuf, '\0', sizeof(szBuf));
     strcat(szBuf,  temp);
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


    char adres_hosta[DLUGOSC_ADRESU];
    short chooseAdress;
    cout << "Choose for setting server IP adress or server hostname: " << endl;
    cout << "Press: " << endl;
    cout << "1: Will be set loacalhost(127.0.0.1) for server adress" << endl;
    cout << "2: Input  server IP adress or server hostname" << endl;
    cin >> chooseAdress;
    if (chooseAdress == 1)
    {
        memset(adres_hosta, '\0', sizeof(adres_hosta));
        strcat(adres_hosta,  "127.0.0.1");
    }
    else if(chooseAdress == 2) {
        cout << "Input  server IP adress or server hostname: ";
        cin >> adres_hosta;
    }else{
        return 0;
    }


    short nPort;
    short choosePort;
    cout << "Set Port number " << endl;
    cout << "Press: " << endl;
    cout << "1: Default Port is 1215" << endl;
    cout << "2: Input  Port number" << endl;
    cin >> choosePort;
    if (choosePort == 1)
    {
        nPort = 1215;
    }
    else if(choosePort == 2) {
        cout << "Input  Port number: ";
        cin >> nPort;
    }else{
        cout << "wrong port number!!!";
        return 0;
    }

    cout << endl << "We are connecting with the Server " << adres_hosta << endl << " on Port " << nPort << endl;


    begining:
    char celsius[256];
    celsius[256] = SetCelsius();


    nRet = WSAStartup(wVersionRequested, &wsaData);
    if(wsaData.wVersion != wVersionRequested)
    {
                        fprintf(stderr, "\n Wrong version\n");
                        return 0;
    }


    StreamClient(adres_hosta, nPort, celsius);
    WSACleanup();

    return 0;
}
