 # Steven Salmons
# Netlab 1b - Web Server

from socket import *
import sys # In order to terminate the program

serverSocket = socket(AF_INET, SOCK_STREAM)

#Prepare a sever socket

serverSocket.bind(('sp1.ecs.csus.edu',8083 ))
serverSocket.listen(1)

while True:
    
    #Establish the connection
    print('Ready to serve...')
   
    connectionSocket, addr = serverSocket.accept()
    
    try:
        message = connectionSocket.recv(1024)#.decode()
        filename = message.split()[1]
        f = open('./'+filename[1:])
        outputdata = f.read()
      
        #Send one HTTP header line into socket  
        connectionSocket.send('HTTP/1.1 200 OK text/html\n\n')        
       
        #Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.send("\r\n".encode())
        connectionSocket.close()
    
    except IOError:
        #Send response message for file not found
        connectionSocket.send('HTTP/1.1 404 File not found\n\n')
        connectionSocket.close()

serverSocket.close()
sys.exit() #Terminate the program after sending the corresponding data
