# Mini_Scada

The goal of the project is to implement a client-server connection. The program allow data to be sent from the server and received by the client. The client is then to be able to edit the way this data is displayed, i.e. a different type of graph, a different color and line thickness, etc.
The program will be implemented using C++ language taking into account object-oriented programming paradigms. The logic of the program will be based on the Qt library, including structures such as QTcpServer, QTcpSocket, QByteArray, etc. 
Basic program elements:
- GUI interface to start the server, generate data and create new clients,
- An interface unique to each client, through which they will be able to connect to the server, display and save data,
- Communication between the client and the server,
- Classes that allow data storage and transfer,
- The ability for the client to save data, both on disk and on the system clipboard,
- Ability for the client to edit the way the data is displayed, including changing the chart type, changing the line thickness, changing the names of the data series, etc.
- Signaling of server status and client connections.