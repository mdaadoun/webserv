#!/usr/bin/python3
from rich import print as printr
from rich.console import Console
from . import data
from colorama import Fore, Back, Style
from prettytable import PrettyTable
import os

def start(config):
    input = config.split(":")[0]
    if input[0][0] == "#":
        return None
    output = config.split(":")[1]
    conf = input.split(",")

    data.request["command"] = conf[0]
    data.request["path"] = conf[1]
    data.request["host"] = conf[2]
    data.request["port"] = conf[3]
    data.request["protocol"] = conf[4]
    return data.request


# generate a config_default.ini file for ./webserv <FILE>
def create_file(content):
    printr("[green]Generated a config_default.ini file.[/green]")
    printr("File content:")
    print(content)
    with open("conf/config_default.ini", "w") as file:
        file.write(content)


def build_table(t):
    t.field_names = [Fore.CYAN + "CONFIG ID", "FILENAME" + Style.RESET_ALL]
    tid = 1
    file_list = os.listdir("conf")
    for f in file_list:
        with open("tst/config.txt", "r") as conffile:
            if conffile.readline() == f:
                color = Fore.GREEN
            else:
                color = Fore.RED
        t.add_row([Fore.YELLOW + str(tid) + Style.RESET_ALL, color + f + Style.RESET_ALL])
        tid += 1


def build_content():
    content = ''
    id = 1
    to = len(data.config) + 1
    print(to)
    while id < to:
        content += '[server]\n'
        for c in data.config[str(id)]:
            if c == "error_page":
                for e in data.config[str(id)][c]:
                    content += c + '_' + e + "=" + data.config[str(id)][c][e] + '\n'
            # elif c == "location":
                # for l in data.config[str(id)][c]:
                #     content += c + '_' + l + "=" + 'allow_methods:' + str(data.config[str(id)][c][l]['allow_methods']) + '\n'
            # else:
            content += c + "=" + str(data.config[str(id)][c]) + '\n'
        id += 1
    return content


def editor():
    printr("[bold yellow]Configs editor:[/bold yellow]")
    console = Console()
    editor_running = True

    while editor_running:
        table = PrettyTable()
        build_table(table)
        print(table)
        printr("[bold green]The green line is the CONFIG file sent to ./webserv [CONFIG][/bold green]")
        ans = console.input(f"""
{data.config_keys['exit'][0]}. quit ({data.config_keys['exit'][1]})
{data.config_keys['default'][0]}. generate the default config ({data.config_keys['default'][1]})
{data.config_keys['add'][0]}. add a manual config ({data.config_keys['add'][1]})
{data.config_keys['select'][0]}. select a config ({data.config_keys['select'][1]})
{data.config_keys['remove'][0]}. remove a config ({data.config_keys['remove'][1]})

[bold yellow](default=generate default file) > [/bold yellow]""")
        if ans in data.config_keys['exit']:
            editor_running = False
        if ans in data.config_keys['select']:
            print("select ID > TODO")
        if ans in data.config_keys['add']:
            print("add new config > TODO")
        if ans in data.config_keys['remove']:
            print("remove new config > TODO")
        elif ans.strip() == '' or ans in data.config_keys['default']:
            conf = build_content()
            create_file(conf)


if __name__ == '__main__':
    editor()
