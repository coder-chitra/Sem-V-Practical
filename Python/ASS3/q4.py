'''
Write a python program to count the number of values of inner lists (use map)
L1 = [ [2, 3, 5, 7], [11,13,17,19], [23, 29], [31,37, 41] ]
Expected output: [4, 4, 2, 3]
'''

def checkLen(item):
    return len(item)

outerList = []

while True :
    n = input("Enter N : ")
    if n.isdigit() :
        n = int(n)
        for i in range(n):
            innerList = [] # to accept inner list elements
            innerList = list(input(f"Enter List Item for list {i+1}: (seperated by spaces) : ").split())
            outerList.append(innerList)
        break
    else :
        print("Invalid Input Entered ! \nEnter Integer")

print("List : ",outerList)
print("Output : ",list(map(checkLen,outerList)))