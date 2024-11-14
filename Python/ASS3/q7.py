'''
7) Write a Python module called “shape”. Write methods for following options in module 
“shape”
a) Calculate area of triangle
b) Calculate area of rectangle
c) Calculate area of circle
d) Calculate area of cone
Use the module “shape” in python program and test it
'''

import shape as s

# menu driven to select one 

while True :
    # printing menu
        print("\na) Calculate area of triangle")
        print("b) Calculate area of rectangle")
        print("c) Calculate area of circle")
        print("d) Calculate area of cone")
        print("e) exit")

        choice = input("\nEnter Choice from above menu : ")

        if choice == 'a':
                area = s.triangle()
                print(f"\nArea of triangle = {area} sq.cm")
        elif choice == 'b':
                area = s.rectangle()
                print(f"\nArea of Rectangle = {area} sq.cm")   
        elif choice == 'c':
                area = s.circle()
                print(f"\nArea of circle = {area} sq.cm") 
        elif choice == 'd':
                area = s.cone()
                print(f"\nTotal Surface Area of cone = {area} sq.cm")     
        elif choice == 'e':
                print("Terminating..............")
                break
        else:
                print("Invalid Input Entered !")     