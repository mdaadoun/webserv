#!/usr/bin/python3
from rich import print as printr
from rich.console import Console

CONFIG = {
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
    "request": {
        "command": "GET",
        "path": "/",
        "host": "0.0.0.0",
        "port": "4242",
        "protocol": "HTTP/1.1"
    },
    "response": {}
}


def start(config):
    input = config.split(":")[0]
    if input[0][0] == "#":
        return None
    output = config.split(":")[1]
    conf = input.split(",")
    CONFIG["request"]["command"] = conf[0]
    CONFIG["request"]["path"] = conf[1]
    CONFIG["request"]["host"] = conf[2]
    CONFIG["request"]["port"] = conf[3]
    CONFIG["request"]["protocol"] = conf[4]
    return CONFIG


# generate a config.ini file for ./webserv <FILE>
def create_file(content):
    printr("[green]Generated a config.ini file.[/green]")
    printr("File content:")
    print(content)
    with open("config.ini", "w") as file:
        file.write(content)


def build_content():
    content = ''
    for c in CONFIG['server']:
        if c == "error_page":
            for e in CONFIG['server'][c]:
                content += c + '_' + e + "=" + CONFIG['server'][c][e] + '\n'
        elif c == "location":
            for l in CONFIG['server'][c]:
                content += c + '_' + l + "=" + 'allow_methods:' + str(CONFIG['server'][c][l]['allow_methods']) + '\n'
        else:
            content += c + "=" + str(CONFIG['server'][c]) + '\n'
    return content


def generate_file():
    printr("[bold yellow]Config file generator:[/bold yellow]")
    console = Console()
    ans = console.input("""
Do you want to generate a quick default config.ini file ?
[bold green]y/yes[/bold green]: generate quick default config.ini file.
[bold red]n/no[/bold red]: generate config.ini with question and answers.

[green](default=yes)[/green] > """)
    print(ans)
    if ans in ['n', 'no']:
        print("QUESTIONS")
    elif ans in ['y', 'yes', '']:
        conf = build_content()
        create_file(conf)
    else:
        print("Not a valid answer, doing nothing.")


if __name__ == '__main__':
    generate_file()
