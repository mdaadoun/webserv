#!/usr/bin/python3
from rich import print as printr
from rich.console import Console
from . import data

def start(config):
    input = config.split(":")[0]
    if input[0][0] == "#":
        return None
    output = config.split(":")[1]
    conf = input.split(",")
    data.config["request"]["command"] = conf[0]
    data.config["request"]["path"] = conf[1]
    data.config["request"]["host"] = conf[2]
    data.config["request"]["port"] = conf[3]
    data.config["request"]["protocol"] = conf[4]
    return data.config


# generate a config.ini file for ./webserv <FILE>
def create_file(content):
    printr("[green]Generated a config.ini file.[/green]")
    printr("File content:")
    print(content)
    with open("config.ini", "w") as file:
        file.write(content)


def build_content():
    content = ''
    for c in data.config['server']:
        if c == "error_page":
            for e in data.config['server'][c]:
                content += c + '_' + e + "=" + data.config['server'][c][e] + '\n'
        elif c == "location":
            for l in data.config['server'][c]:
                content += c + '_' + l + "=" + 'allow_methods:' + str(data.config['server'][c][l]['allow_methods']) + '\n'
        else:
            content += c + "=" + str(data.config['server'][c]) + '\n'
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
