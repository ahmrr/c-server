from socket import *

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 8888
BUFFER_SIZE = 4096

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((SERVER_HOST, SERVER_PORT))

message = input('send: ')

while message != "q":
    client_socket.send(message.encode())
    response = client_socket.recv(BUFFER_SIZE)

    print('received the following from the server:\n\n')
    print(response)
    print('\n\n')
    message = input('send: ')

client_socket.close()
