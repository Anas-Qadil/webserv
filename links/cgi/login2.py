#!/usr/bin/env python

import cgi
import cgitb

cgitb.enable()  # for troubleshooting

form = cgi.FieldStorage()

username = form.getvalue("username")
password = form.getvalue("password")

print("Content-type: text/html")
print()
print("<html>")
print("<body>")
print("Username:", username)
print("<br>")
print("Password:", password)
print("</body>")
print("</html>")
