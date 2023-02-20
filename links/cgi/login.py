#!/usr/bin/python

import cgi

# Get the form data
form = cgi.FieldStorage()

# Get the "uname" and "password" parameters
uname = form.getvalue("username")
password = form.getvalue("password")

# Print the "uname" and "password" values
print("Content-type: text/html\n")
print("Username:", uname)
print("Password:", password)
