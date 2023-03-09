from socket import *

SERVER_HOST = 'localhost'
SERVER_PORT = 8000
BUFFER_SIZE = 1024

NUM_ECHOS = 3
current_echo_count = 0

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((SERVER_HOST, SERVER_PORT))

while current_echo_count < NUM_ECHOS:
    message = input('Input: ')

    client_socket.send(message.encode())
    response = client_socket.recv(BUFFER_SIZE)

    print('Received "', response.decode(), '" from the server')
    current_echo_count += 1

client_socket.close()
