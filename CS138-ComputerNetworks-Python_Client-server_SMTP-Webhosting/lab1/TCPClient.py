# Steven Salmons
# PLab 1a - TCP Client
# TCPClient code from lecture slides


from socket import *

clientSocket = socket(AF_INET, SOCK_STREAM)  # create TCP socket for server, repote port 32023
clientSocket.connect(('sp1.ecs.csus.edu', 32023))

sentence = raw_input('Input lowercase sentence:')

clientSocket.send(sentence.encode())

modifiedSentence = clientSocket.recv(1024)

print modifiedSentence.decode()

clientSocket.close()

