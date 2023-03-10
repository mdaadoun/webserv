import os

env_vars = os.environ
print("""
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-rbsA2VBKQhggwzxH7pPCaAqO46MgnOM80zW1RWuH61DGLwZJEdK2Kadq2F9CUG65" crossorigin="anonymous">
    <title>Python Script Demo</title>
  </head>
  <body>
  <div class="container">
""")
print("<h1>python cgi script ok!</h1>")
name = ""
password = ""
identity = ''
query = []
for var, value in env_vars.items():
    if "QUERY_STRING" in var:
        query = value.split("&")

for q in query:
    if "=" in q:
        s = q.split("=")
    else:
        s = query.split("=")
    if s[0] == "name":
        name = s[1]
    if s[0] == "password":
        password = s[1]
    if s[0] == "identity":
        identity = s[1]

if name:
    print("<p>Hello, <b class='text-primary'>", name, "</b></p>")
    print("<p>I hacked your password, it is <b class='text-primary'>", password, "</b></p>")
print("<pre>")
for var, value in env_vars.items():
    print(f"{var}: {value}")
print("</pre>")


print("<h2>PUBLIC data</h2>")
current_file_dir = os.path.dirname(os.path.abspath(__file__))
print("<pre>")
with open(current_file_dir + "/data.txt") as file:
    for line in file:
        if "PRIVATE_DATA" in line:
            break
        print(line)
print("</pre>")

for var, value in env_vars.items():
    if "REQUEST_METHOD" in var:
        query = value


print('<h2>PRIVATE data</h2>')
if identity != "hello":
    print("<p class='text-primary'>access by typing <b>hello</b> in form</p>")

    print("""
    <form class="row g-3" action="index.py">
      <div class="col-auto">
        <input type="text" class="form-control"  name="identity" id="identity" placeholder="type hello">
      </div>
      <div class="col-auto">
        <button type="submit" class="btn btn-primary mb-3">Confirm identity</button>
      </div>
    </form>
    """)
else:
    print("<pre>")
    with open(current_file_dir + "/data.txt") as file:
        display = False
        for line in file:
            if "PRIVATE_DATA" in line:
                display = True
            if display:
                print(line)
    print("</pre>")


print("""
</div>

  </body>
</html>
""")

# FORMULAIRE POSTING NAME AND TITLE AND ADAPT SCRIPT IF GET or POST REQUEST
# Display the content/data.txt file from the script, the PUBLIC data part, and the PRIVATE data part if a name was provided in the form
