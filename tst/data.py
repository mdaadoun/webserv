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
    4. run tests with remote (nginx) on port 8080 (r)
        41. run the tests bloquants on pyserv (p)
        42. run the tests bloquants on webserv (w)
    5. (todo) run the tester web application (will be default)"""

menu_keys = {
    "exit": ['0', 'q'],
    "help": ['1', 'h'],
    "app": ['5', 'a'],
    "editor": ['2', 'e'],
    "config": ['3', 'c'],
    "pyserv": ['41', 'p'],
    "webserv": ['42', 'w'],
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
    
    * [bold yellow]test all servers[/bold yellow]: 
        will test the 3 servers and compare results (REMOTE, PYTHON and C++).
            * [bold magenta]./run.py -a or --all[/bold magenta]
    
    * notes:
        [italic white]* for -w the tester will generate multiple config files and run multiple time ./webserv config_default.ini
        * don't add tests manually to ./tst/tests.txt, use -t, the tests editor.
        * for remote and the --all option, the port is 8080 by default and will ignore the tests ports.[/italic white]
"""

config = {
    "server": {
        "server_name": "webserv",
        "listen": "0.0.0.0:4242",
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
            "/cgi": {
                "allow_methods": "GET POST DELETE"
            }
        }
    },
}

request = {
    "command": "GET",
    "path": "/",
    "host": "0.0.0.0",
    "port": "4242",
    "protocol": "HTTP/1.1"
}

response = {

}
