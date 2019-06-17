# Steven Salmons
# PLab 1a - UDP/TCP
# TCPServer code directly from lecture slides

from socket import *

serverPort = 32023
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('sp1.ecs.csus.edu', 32023))
serverSocket.listen(1)

print 'Ther server is ready to receive'

while True:

    connectionSocket, addr = serverSocket.accept()
    sentence = connectionSocket.recv(1024).decode()
    capitalizedSentence = sentence.upper()
    connectionSocket.send(capitalizedSentence.encode())
    connectionSocket.close()
