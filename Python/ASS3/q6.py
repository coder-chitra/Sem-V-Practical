'''6) Write a python program to eliminate all words that are shorter than 4 letters from a list 
of words. Use filter()'''

check = lambda x : (len(x) >= 4)

l = []

while True :
    n = input("Enter N : ")
    if n.isdigit() :
        n = int(n)
        for i in range(n):
            li = input(f"Enter List Item {i+1}:")
            l.append(li)
        print("List Items >= length 4 : ",list(filter(check,l)))
        break
    else :
        print("Invalid Input Entered ! \nEnter Integer")
