# 1) Write a python program to print date, time for today and now using function

import datetime

x = datetime.datetime.now()

# Date 
print("Date : ",x.strftime("%d/%m/%Y"))

# Time
print("Time : ",x.strftime("%H.%M"))