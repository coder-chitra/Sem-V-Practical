import socket
username=input("Enter the Username: ")
cs=socket.socket()
cs.connect(("localhost",12345))
cs.send(username.encode())
response=cs.recv(1024).decode()
print(response)
