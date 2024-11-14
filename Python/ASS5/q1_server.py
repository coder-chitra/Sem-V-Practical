import socket,datetime
ss=socket.socket()
ss.bind(("localhost",12345))
ss.listen(5)
print("Waiting for Client")
while True:
    cs,addr=ss.accept()
    print("Connected")
    username=cs.recv(1024).decode()
    current_time=datetime.datetime.now()
    hour=current_time.hour
    if hour<=12:
        greeting="Good Morning"
    elif hour<=17:
        greeting="Good Afternoon"
    else:
        greeting="Good Evening"
    response=f"{greeting},{username}"
    cs.send(response.encode())
    choice=input("Do you want to continue (yes or no): ")
    if choice=="yes":
        continue
    elif choice=="no":
        break
    else:
        print("Enter valid input")

ss.close()
