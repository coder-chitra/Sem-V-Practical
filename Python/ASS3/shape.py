PI = 3.14159

#  Area of Triangle
def triangle():
    while True :
        base = input("\nEnter Base of Triangle in cm : ")
        height = input("Enter height of Triangle in cm : ")
        if height.replace('.','',1).isdigit() and height.replace('.','',1).isdigit() : # condition check for float n
            
            base = float(base) 
            height = float(height)

            return (0.5 * base * height)        
        else :
             print("\nInvalid Input Entered!\nEnter Valid Integers greater than 0")

#  Area of Rectangle
def rectangle():
    while True :
        l = input("\nEnter length of Rectangle in cm : ")
        b = input("Enter breadth of Rectangle in cm : ")
        if l.replace('.','',1).isdigit() and b.replace('.','',1).isdigit() : # condition check for float n
            
            l = float(l) 
            b = float(b)

            return l*b        
        else :
             print("\nInvalid Input Entered!\nEnter Valid Integers greater than 0")            


#  Area of Circle
def circle():
    while True :
        r = input("Enter radius of circle in cm : ")
        if r.replace('.','',1).isdigit() : # condition check for float n
            
            r = float(r) 

            return (PI*(r**2))        
        else :
             print("\nInvalid Input Entered!\nEnter Valid Integers greater than 0")   

#  Area of Cone
def cone():
    while True :
        r = input("\nEnter Radius of the base of the cone cm : ")
        l = input("Enter slant height of cone in cm : ")
        if r.replace('.','',1).isdigit() and l.replace('.','',1).isdigit() : # condition check for float n
            
            r = float(r) 
            l = float(l)

            return (PI * r * (r + l))
        else :
             print("\nInvalid Input Entered!\nEnter Valid Integers greater than 0")         