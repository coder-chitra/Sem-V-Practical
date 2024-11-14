# Write a Python function to compute ‘gcd’ and ‘lcm’ of two numbers

def gcd(n1 , n2):
    if n1 == 0 :
        return n2
    return gcd(n2 % n1, n1)


while True :
    n1 = input("Enter Number 1 : ")
    n2 = input("Enter Number 2 : ")
    if n1.replace('-','',1).isdigit() and n2.replace('-','',1).isdigit() : # condition check for negative n
        
        n1 = int(n1) 
        n2 = int(n2) 
        if n1 == 0 and n2 == 0 : # ZeroDivisionError condition checked
            print("Enter Non Zero Input  ")
            continue
        else :
            gcd = gcd(n1,n2)
            lcm = (n1 / gcd) * n2

            print(f"GCD of ({n1},{n2}) : {abs(gcd)}\nLCM of ({n1},{n2}) : {abs(lcm)}")
            break
    else :
        print("Invalid Input Entered \nEnter Valid Integers ")