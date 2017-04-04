# Temperature-Calculator
Temperature Calculator is Client- Server Console Application written in C++ using Winsock

Temperature Calculator is Client/Server Application, which was writing in C++. I Used Winscok to create net application via TCP protocol.
Base function of this application is very simply -  calculates values of temperatures in various scales degrees.

The input is value of temperature in Celsius grade
The output are values of temperature in grade: Kelvin, Fahrenheit, Réaumur scale

How to run:
1. First You must run server via Cmd - 
  - put in the Console "Tserv", 
  - then You must set port number: Choose default setting(key number "1") or put from keyboard number of port (key number "2")
2. Second You must run Client:
  - put in the Console "Tclient",
  2.1. You must choose Your server adress:
       - If you press KeyNum "1" option, then adress of server will be default assign to the localhost(127.0.0.1) 
       - If you press KeyNum "2" option, then adress of server must input manually by yoursefl...
  2.2. Set Port Number:
       - If you press KeyNum "1" - port number will be setting default(1215)
       - If you press KeyNum "2" - number of port, You must input manually from the keyboard
  2.3. Input temperature in Celsius scale - NOW You input value of temperature wich will be calculate (for example 1250), 
       then press "enter" and its all :-) 
