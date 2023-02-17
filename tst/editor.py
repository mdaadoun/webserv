from . import config
from colorama import Fore, Back, Style
from prettytable import PrettyTable
from rich import print as printr
from rich.console import Console
from . import data


def get_request(line):
    request_line = line.split(":")[0]
    conf = request_line.split(",")
    active = 'yes'
    if line[0] == "#":
        conf[0] = conf[0][1:]
        active = 'no'
    request_dict = {
        "command": conf[0],
        "path": conf[1],
        "host": conf[2],
        "port": conf[3],
        "protocol": conf[4],
        "active": active
    }
    return request_dict


def build_table(f, t):
    new_file = ''
    t.field_names = [Fore.CYAN + "TEST ID", "COMMAND", "PATH", "HOST", "PORT", "PROTOCOL" + Style.RESET_ALL]
    line = f.readline()
    tid = 1
    while line:
        new_file += line
        conf = get_request(line)
        color = Fore.GREEN
        if conf["active"] == 'no':
            color = Fore.RED
        t.add_row([Fore.YELLOW + str(tid) + Style.RESET_ALL, color + conf["command"], conf["path"], conf["host"],
                   conf["port"], conf["protocol"] + Style.RESET_ALL])
        line = f.readline()
        tid += 1
    return new_file


# def update_file():
#     pass

def delete_row(t):
    t.del_row(1)
    # update_file()


def activate_test(file, tid):
    file = file.split('\n')
    print(len(file))
    if tid.isdigit() and int(tid) > 0:
        if file[int(tid) - 1][0] == '#':
            file[int(tid) - 1] = file[int(tid) - 1][1:]
        else:
            file[int(tid) - 1] = '#' + file[int(tid) - 1]
        file = '\n'.join(file)
        with open("tst/tests.txt", "w") as filename:
            filename.write(file)
    else:
        print("Not a correct index")

def add_test():
    test = '\n'
    ans = input("SET COMMAND ? (default GET) > ")
    if ans.strip() == '':
        ans = 'GET'
    test += ans + ','

    ans = input("SET PATH ? (default /) > ")
    if ans.strip() == '':
        ans = '/'
    test += ans + ','

    ans = input("SET ADDRESS ? (default 0.0.0.0) > ")
    if ans.strip() == '':
        ans = '0.0.0.0'
    test += ans + ','

    ans = input("SET PORT ? (default 4242) > ")
    if ans.strip() == '':
        ans = '4242'
    test += ans + ','

    ans = input("SET PROTOCOL ? (default HTTP/1.1) > ")
    if ans.strip() == '':
        ans = 'HTTP/1.1'
    test += ans + ':'
    with open("tst/tests.txt", "a") as f:
        f.write(test)

def start():
    printr("[bold yellow]Tests editor:[/bold yellow]")
    editor_running = True
    console = Console()
    while editor_running:
        table = PrettyTable()
        with open("tst/tests.txt", "r") as filename:
            file = build_table(filename, table)
        # clear terminal ?
        print(table)
        print(f"""
{data.editor_keys['exit'][0]}. quit ({data.editor_keys['exit'][1]})
{data.editor_keys['add'][0]}. add a test ({data.editor_keys['add'][1]})
{data.editor_keys['silent'][0]}. silent/activate a test ({data.editor_keys['silent'][1]})
{data.editor_keys['remove'][0]}. remove a test ({data.editor_keys['silent'][1]})
""")
        ans = console.input("[bold yellow](default=quit) > [/bold yellow]")
        if ans.strip() == '' or ans in data.editor_keys['exit']:
            editor_running = False
        elif ans in data.editor_keys['add']:
            add_test()
        elif ans in data.editor_keys['silent']:
            tid = console.input("[bold green]TEST INDEX > [/bold green]")
            activate_test(file, tid)
        elif ans in data.editor_keys['silent']:
            print("remove a test")
