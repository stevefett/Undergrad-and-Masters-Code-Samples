from socket import *
import sys

if len(sys.argv) <= 1:
    print('Usage : "python Address Of Proxy Server')
    sys.exit(2)


 # Create a server socket, bind it to a port and start listening
tcpSerPort = 1337
tcpSerSock = socket(AF_INET, SOCK_STREAM)
tcpSerSock.bind((sys.argv[1], tcpSerPort))
tcpSerSock.listen(1)

while 1:
    # Strat receiving data from the client
    print('Ready to serve...')
    tcpCliSock, addr = tcpSerSock.accept()
    print('Received a connection from:', addr)
    message = tcpCliSock.recv(1024)
    # Fill in end.
    print(message)
    # Extract the filename from the given message
    print(message.split()[1])
    filename = message.split()[1].partition("/")[2]
    print(filename)
    fileExist = False
    filetouse = "/" + filename

    print(filetouse)

    try:
        # Check wether the file exist in the cache
        f = open(filetouse[1:], "r")
        outputdata = f.readlines()
        fileExist = "true"
        # ProxyServer finds a cache hit and generates a response message
        tcpCliSock.send("HTTP/1.0 200 OK\r\n")
        tcpCliSock.send("Content-Type:text/html\r\n")

        for c in range(0, len(outputdata)):
            tcpCliSock.send(outputdata[c])

        print('Read from cache')

    # Error handling for file not found in cache
    except IOError:

        if not fileExist:
            # Create a socket on the proxyserver
            c = socket(AF_INET, SOCK_STREAM)
            hostn = filename.replace("www.","",1)
            print(hostn)
            # Fill in end.

            try:
                c.connect((hostn, 80))
                fileobj = c.makefile('r', 0)
                fileobj.write("GET "+"http://" + filename + " HTTP/1.0\n\n")
                # Read the response into buffer
                # Fill in start.
                # Read the response into buffer
                buff = fileobj.readlines()

                # Create a new file in the cache for the requested file.
                # Also send the response in the buffer to client socket
                # and the corresponding file in the cache
                tmpFile = open("./" + filename, "wb")
                for i in range(0, len(buff)):
                    tmpFile.write(buff[i])
                    tcpCliSock.send(buff[i])

            except:
                print('Illegal request')

        else:
            tcpCliSock.end("HTTP/1.0 404 Not Found\r\n")
            tcpCliSock.send("Content-Type:text/html\r\n")

    # Close the client and the server sockets
    tcpCliSock.close()
