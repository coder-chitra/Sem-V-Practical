'''Write a python function to find the factorial of a given number. Accept number from 
user.'''

def factorial(n) :
    if(n == 1 or n == 0):   # base condition
        return 1
    else :
        return n * factorial(n-1)
    
while True :
    n = input("Enter N : ")
    if n.isdigit() :
        n = int(n)
        if n < 0 or n > 999 :
            print("Invalid Input Entered ! \nEnter Integer (0-999)")
            continue
        else :
            print(f"Factorial of {n} : {factorial(n)}")
            break
    else :
        print("Invalid Input Entered ! \nEnter Integer (0-999)")