class Student:
    def __init__(self):
        self.name = "Aanand Ingle"
        self.age = 18
        self.grade = "O"

    def __str__(self):
        return f"Name: {self.name}, Age: {self.age}, Grade: {self.grade}"