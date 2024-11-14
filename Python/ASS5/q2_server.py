import socket
ss=socket.socket()
ss.bind(("localhost",23456))
ss.listen(5)
print("Waiting for Client")
while True:
    cs,addr=ss.accept()
    print("Connected")
    filename=cs.recv(1024).decode()
    try:
        with open(filename,'r') as f:
            data=f.read()
        cs.send(data.encode())
    except:
        print("Enter valid filename")
        cs.send("Invalid Filename".encode())
    choice=input("Do you want to continue (yes or no): ")
    if choice=="yes":
        continue
    elif choice=="no":
        break
    else:
        print("Enter valid input")
ss.close()
