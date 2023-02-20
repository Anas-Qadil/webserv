#!/usr/bin/python

import cgi
import os

# Get the form data
form = cgi.FieldStorage()

# Get the file data
file_data = form["file"].file.read()

# Get the file name
file_name = form["file"].filename

# Create the file in the specified path
path = "/Users/aaitoual/Desktop/Web_server/content"
with open(os.path.join(path, file_name), "wb") as f:
    f.write(file_data)

# Print a message to confirm that the file was created
print("Content-type: text/html\n")
print("File '{}' successfully created in {}".format(file_name, path))
