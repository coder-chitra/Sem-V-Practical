import socket
import pickle
from student import Student


# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
client_socket.connect(('localhost', 12345))

print("Connected to server")

# Receive the Student object from the server
student = pickle.loads(client_socket.recv(1024))

# Display the details of the Student object
print("Student Details:")
print(student)

# Close the socket
client_socket.close()