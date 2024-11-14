import socket
import pickle
from student import Student

# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to a address and port
server_socket.bind(('localhost', 12345))

# Listen for incoming connections
server_socket.listen(1)

print("Server is listening...")

# Create a Student object
student = Student()

# Accept incoming connection
client_socket, address = server_socket.accept()

print("Connection established with client")

# Send the Student object to the client
client_socket.sendall(pickle.dumps(student))

# Close the socket
client_socket.close()
server_socket.close()