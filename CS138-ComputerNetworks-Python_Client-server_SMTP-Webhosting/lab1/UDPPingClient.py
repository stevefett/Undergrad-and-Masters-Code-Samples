import time
from socket import *


serverAddress = 'sp1.ecs.csus.edu'
serverPort = 32023

print '\nPinging %s:%d' % (serverAddress, serverPort)

for pings in range(10):
    clientSocket = socket(AF_INET, SOCK_DGRAM)
    clientSocket.settimeout(1)
    message = 'steven salmons lab1.'
    addr = (serverAddress, serverPort)

    start = time.time()
    clientSocket.sendto(message, addr)
    try:
        data, server = clientSocket.recvfrom(1024)
        elapsed = time.time() - start
        print '\tREPLIED : PING %s RTT = %.3f s' % (pings + 1 , elapsed)
    except timeout:
        print '\tRequest timed out'
