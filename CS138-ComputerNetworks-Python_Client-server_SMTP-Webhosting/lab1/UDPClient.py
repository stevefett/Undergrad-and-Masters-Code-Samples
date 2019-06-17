# Steven Salmons
# PLab 1a - UDP Client
# UDPClient code from lecture slides


from socket import *

serverName = 'sp1.ecs.csus.edu'
serverPort = 32023

clientSocket = socket(AF_INET, SOCK_DGRAM)

message = raw_input('Input lowercase sentence:')

clientSocket.sendto (message.encode(),(serverName, serverPort))

modifiedMessage, serverAddress = clientSocket.recvfrom(2048)

print modifiedMessage.decode()

clientSocket.close()
