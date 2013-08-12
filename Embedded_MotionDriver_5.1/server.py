import socket
import struct

server_socket = socket.socket()
server_hostname = socket.gethostname()
server_port = 1337

server_socket.bind((m_server_hostname, m_server_port))

server_socket.listen(0)

server_running = True
connection_socket = None

while server_running:
	

while True:
	connection_socket, connection_address = server_socket.accept()
	
	connection_socket.read(8)
