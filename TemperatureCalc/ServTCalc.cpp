#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <winsock.h>
#include <sstream>

using namespace std;

#define PRINTERROR(s)	\
 	fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

void ConvertScale(int degree)
{
     double kelwin = 273.15 + degree;
     double faranhajt = (32 + (9/5)) * degree;
     double reumar = 0.8 * degree;
     cout << "Temperature in Celsius scale: " << degree << "[\370C]" << " for: " << endl;
     cout << "Kelvin scale is: " <<  kelwin << " [K]" << endl;
     cout << "Fahrenheit scale is: " <<  faranhajt << " [\370F]" << endl;
     cout << "Reaumur scale is: " <<  reumar << " [\370Re]" << endl;
}


void StreamServer(short nPort)
{

     WORD wVersionRequested = MAKEWORD(1,1);
    WSADATA wsaData;


    int nRet2;
    nRet2 = WSAStartup(wVersionRequested, &wsaData);
    if (wsaData.wVersion != wVersionRequested)
    {
         	fprintf(stderr,"\n Wrong version\n");
    }

     SOCKET listenSocket;
     SOCKET remoteSocket;
     char szBuf[256];
     int nRet;

     listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(listenSocket == INVALID_SOCKET)
     {
      PRINTERROR("socket()");
      return;
      }
      cout << "listenSocket is: "<< listenSocket << endl;
      SOCKADDR_IN saServer;
      saServer.sin_family = AF_INET;
      saServer.sin_addr.s_addr = INADDR_ANY;
      saServer.sin_port = htons(nPort);


      nRet = bind(listenSocket, (LPSOCKADDR)&saServer, sizeof(sockaddr));
      if(nRet == SOCKET_ERROR)
      {
            PRINTERROR("bind()");
            closesocket(listenSocket);
            return;
      }

      int nLen;
      nLen = sizeof(SOCKADDR);
      nRet = gethostname(szBuf, sizeof(szBuf));
      if(nRet == SOCKET_ERROR)
      {
              PRINTERROR("gethostanem()");
              closesocket(listenSocket);
              return;
      }

      cout << "Name of Server : " << szBuf << " Listen on port: " << nPort << endl;
      cout << "Let's start to listen !!!!" << endl;

      nRet = listen(listenSocket, SOMAXCONN);
      if(nRet == SOCKET_ERROR)
      {
              PRINTERROR("listen()");
              closesocket(listenSocket);
              return;
      }

      cout << "Blocking Connection" << endl;

      remoteSocket =accept(listenSocket, NULL, NULL);
      cout << "listenSocket set as: "<< listenSocket << endl;
      cout << "remoteSocket set as: "<< remoteSocket << endl;
      if(remoteSocket == INVALID_SOCKET)
      {
                      PRINTERROR("accept()");
                      closesocket(listenSocket);
                      return;
      }
      memset(szBuf, '\0', sizeof(szBuf));
      nRet = recv(remoteSocket, szBuf, sizeof(szBuf), 0);

      if(nRet == INVALID_SOCKET)
      {
              PRINTERROR("recv()");
              closesocket(listenSocket);
              closesocket(remoteSocket);
              return;
      }

      cout << "Data received from Client: " << szBuf << endl;
      short ktemp;
      ktemp = atoi(szBuf);
      ConvertScale(ktemp);
      strcat(szBuf, " Celsius degree was Calculated in various scale of temperature.. \n **** Best regards from the Server ****");
      nRet = send(remoteSocket, szBuf, strlen(szBuf), 0);

      cout << "listenSocket set as: "<< listenSocket << endl;
      cout << "remoteSocket set as: "<< remoteSocket << endl;

      closesocket(remoteSocket);
      closesocket(listenSocket);
      WSACleanup();

      return;

}

int main(int argc, char *argv[])
{
    short nPort;
    int choose;
    cout << "Calculator of Temperature Scale (Server TCP) is running!" << endl;
    cout << "Set number of Port listening : " << endl;
    cout << "1: default (1215 port number)     2: Input number of port listening" << endl;
    cin >> choose;
    if (choose == 1)
    {
        nPort = 1215;
    }
    else if(choose == 2) {
        cin >> nPort;
    }else{
        return 0;
    }



    StreamServer(nPort);

    begining:
    cout << "\n********SERVER   STOPPED:******** " << endl;
    cout << "If You want run server one more time - PRESS \"1\": " << endl;
    cout << "If You want Quit - PRESS \"2\" or any key: " << endl;
    short quitOrContinue;
    cin >> quitOrContinue;


    if(quitOrContinue == 1)
    {
        StreamServer(nPort);
    }


    if(quitOrContinue == 1)
    {
        goto begining;

    }else if(quitOrContinue == 2)
    {
        return 0;
    }else{
        return 0;
    }


    return 0;
}

