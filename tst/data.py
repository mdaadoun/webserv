title = """[bold yellow]
==============
WEBSERV TESTER
==============
[/bold yellow]"""

menu = """ [bold yellow]MENU[/bold yellow]
    
    0. to exit (q)
    1. display help (h)
    2. tests editor (e)
    3. configs editor (c)
    4. run tests with remote (nginx) (r)
    5. run tests on pyserv (p)
    6. run tests on webserv (w) (default)"""

menu_keys = {
    "exit": ['0', 'q'],
    "help": ['1', 'h'],
    "app": ['7', 'a'],
    "editor": ['2', 'e'],
    "config": ['3', 'c'],
    "pyserv": ['5', 'p'],
    "webserv": ['6', 'w'],
    "remote": ['4', 'r']
}

editor_keys = {
    "exit": ['0', 'q'],
    "add": ['1', 'a'],
    "silent": ['2', 's'],
    "remove": ['3', 'r']
}

config_keys = {
    "exit": ['0', 'q'],
    "default": ['1', 'd'],
    "add": ['2', 'a'],
    "select": ['3', 's'],
    "remove": ['4', 'r']
}

help = """ [bold yellow]HELP[/bold yellow]

    * [bold yellow]default[/bold yellow] (./run.py) without option display this help. 
        * [italic](option -h and --help will work too)[/italic]
        
    * [bold yellow]tests editor[/bold yellow]:
        display, add, delete, activate or deactivate tests.
            * [bold magenta]./run.py -e or --editor[/bold magenta]
    
    * [bold yellow]config file[/bold yellow]: 
        will generate a [bold green]conf/config_*.ini[/bold green] files with default or manual add/delete/select questions/answers parameters.
            * [bold magenta]./run.py -c or --conf[/bold magenta]
    
    * [bold yellow]test cpp server (webserv)[/bold yellow]: 
        will test [bold green]CPP WEBSERV[/bold green] with ./webserv <CONFIG_FILE>.
            * [bold magenta]./run.py -w or --webserv[/bold magenta]
    
    * [bold yellow]test remote server[/bold yellow]: 
        will test [bold green]REMOTE[/bold green] server (NGINX’s server if possible). (8080 port only)
            * [bold magenta]./run.py -r or --remote[/bold magenta]
            * [italic]Configure your remote port to listen 8080.[/italic]
    
    * [bold yellow]test local python server[/bold yellow]: 
        will test local [bold green]PYTHON[/bold green] HTTP web server.
            * [bold magenta]./run.py -p or --pyserv[/bold magenta]
    
    * notes:

        [italic white]* for -w the tester will generate multiple config files and run multiple time ./webserv config_default.ini
        * don't add tests manually to ./tst/tests.txt, use -t, the tests editor.
        * for remote and the --all option, the port is 8080 by default and will ignore the tests ports.[/italic white]
"""

"""
DO THIS

[server]
server_name=webserv1
listen=0.0.0.0:2424
root=./www/html
index=index.html
autoindex=on
client_body_limit=4096
error_page_400=400.html
error_page_401=401.html
error_page_403=403.html
error_page_404=404.html
error_page_405=405.html
error_page_410=410.html
error_page_413=413.html
error_page_500=500.html
error_page_503=503.html
location:/
{
	allow_methods=GET
	allow_methods2=GET POST DELETE
}
location:/content
{
	allow_methods=GET
}
location:/cgi-bin
{
	allow_methods=GET POST DELETE
}
cgi_type=py
cgi_interpreter=/usr/bin/python3
cgi_directory=cgi-bin

[server]
server_name=webserv2
listen=0.0.0.0:6969
root=./www/html
index=index.html
autoindex=off
client_body_limit=4096
error_page_400=400.html
error_page_401=401.html
error_page_403=403.html
error_page_404=404.html
error_page_405=405.html
error_page_410=410.html
error_page_413=413.html
error_page_500=500.html
error_page_503=503.html
location:/
{
	allow_methods=GET
}
location:/content
{
	allow_methods=GET
}
location:/cgi-bin
{
	allow_methods=GET POST DELETE
}
"""

config = {
    "1": {
        "server_name": "webserv1",
        "listen": "0.0.0.0:2424",
        "root": "./www/html",
        "index": "index.html",
        "autoindex": "off",
        "client_body_limit": "4096",
        "error_page": {
            "400": "400.html",
            "401": "401.html",
            "403": "403.html",
            "404": "404.html",
            "405": "405.html",
            "410": "410.html",
            "413": "413.html",
            "500": "500.html",
            "503": "503.html"
        },
        "location": {
            "/": {
                "allow_methods": "GET"
            },
            "/content": {
                "allow_methods": "GET"
            },
            "/cgi-bin": {
                "allow_methods": "GET POST DELETE"
            }
        }
    },
    "2": {
        "server_name": "webserv2",
        "listen": "0.0.0.0:2244",
        "root": "./www/html",
        "index": "index.html",
        "autoindex": "on",
        "client_body_limit": "4096",
        "location": {
            "/cgi-bin": {
                "root": "www/html/cgi-bin",
                "upload_dir": "www/html/content",
                "cgi_extensions": ["python"],
                "disabled_methods": [""],
                "max_client_body_size": 2500000,
            },
            "/": {
                "allow_methods": "GET"
            },
            "/content": {
                "allow_methods": "GET POST"
            }
        }
    },
    "3": {
        "server_name": "webserv3",
        "listen": "0.0.0.0:4422",
        "root": "./www/html",
        "index": "index.html",
        "autoindex": "on",
        "client_body_limit": "256",
        "disabled_methods": ["POST", "DELETE", "GET"]
    },
}

test = {
    'request': {
        "command": "GET",
        "path": "/",
        "host": "0.0.0.0",
        "port": "80",
        "protocol": "HTTP/1.1"
    },
    'response': {
        'Status': '000',
        'Server': '',
        'Date': '',
        'Content-Type': 'text/html',
        'Last-Modified': '',
        'Transfer-Encoding': 'chunked',
        'Connection': 'keep-alive',
        'ETag': '',
        'Content-Encoding': 'gzip'
    }
}
