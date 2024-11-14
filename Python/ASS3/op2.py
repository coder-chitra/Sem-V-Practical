'''Write a Python script to print the current date in following format “Sun May 29 
02:26:23 IST 2017'''

from datetime import datetime

# Get the current date and time
now = datetime.now()

# Format the date and time according to the specified format
formatted_date = now.strftime("%a %b %d %H:%M:%S IST %Y")

# Print the formatted date and time
print(formatted_date)
