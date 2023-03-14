from socket import *

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 8080
BUFFER_SIZE = 4096

sock = socket(AF_INET, SOCK_STREAM)

sock.bind((SERVER_HOST, SERVER_PORT))
sock.listen()
conn, addr = sock.accept()

data = conn.recv(BUFFER_SIZE)
conn.send("Hello World!")
