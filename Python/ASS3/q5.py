'''5) Write a python program to double a given number and add two numbers using lambda()'''

double = lambda num : num * 2   # lambda fun to double a num

add2 = lambda num1 , num2 : num1 + num2 # lambda fun to add 2 a numbers


print("\nTo Double a Number ")
# to double a number 
while True :
    n = input("Enter a Number : ")
    if(n.replace('-','',1).isdigit()):
        n = int(n)
        print(f"Double of {n} = {double(n)}")
        break
    else :
        print("Invalid Input Entered!\nEnter Valid Integers")

print("\n\nTo Add 2 Numbers")
# for sum
while True :
    n1 = input("Enter Number 1 : ")
    n2 = input("Enter Number 2 : ")
    if n1.replace('-','',1).isdigit() and n2.replace('-','',1).isdigit() : # condition check for negative n
        
        n1 = int(n1) 
        n2 = int(n2) 
        print(f"Sum of {n1} and {n2} = ",add2(n1,n2))
        break
    else :
        print("Invalid Input Entered \nEnter Valid Integers ")