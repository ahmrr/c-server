from socket import *

SERVER_HOST = 'localhost'
SERVER_PORT = 5555
BUFFER_SIZE = 1024

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((SERVER_HOST, SERVER_PORT))

message = input('send: ')

while message != "q":
    client_socket.send(message.encode())
    response = client_socket.recv(BUFFER_SIZE)

    print('received the following from the server:\n\n' + response.decode() + '\n\n')
    message = input('send: ')

client_socket.close()
