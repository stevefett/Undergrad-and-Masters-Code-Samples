# Steven Salmons
# PLab 1a - UDP 
# UDPServer code directly from lecture slides

from socket import *

serverPort = 32023

serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('sp1.ecs.csus.edu', 32023))

print "The server is ready to receive"

while True:
    message, clientAddress = serverSocket.recvfrom(2048)
    modifiedMessage = message.decode().upper()
    serverSocket.sendto(modifiedMessage.encode(), clientAddress)
