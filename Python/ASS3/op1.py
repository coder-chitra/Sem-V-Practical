''' Write a python program to write a lambda function to calculate the square of number
from the given list.
Expected Answer:
The initial list of numbers: [3, 22, 36, 45, 56, 77, 87, 93]
'''


numbers = [3, 22, 36, 45, 56, 77, 87, 93]

numbers = list(map(lambda x : x * x,numbers))

print(numbers)