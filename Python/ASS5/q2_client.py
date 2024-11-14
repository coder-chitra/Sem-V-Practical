import socket
filename=input("Enter filename: ")
cs=socket.socket()
cs.connect(("localhost",23456))
cs.send(filename.encode())
data=cs.recv(1024).decode()
print(data)
