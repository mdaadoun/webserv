from . import config
from colorama import Fore, Back, Style
from prettytable import PrettyTable
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


def start():
    editor_running = True
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
        ans = input("(default=quit) > ")
        if ans.strip() == '' or ans in data.editor_keys['exit']:
            editor_running = False
        elif ans in data.editor_keys['add']:
            print("add a test")
        elif ans in data.editor_keys['silent']:
            tid = input("TEST INDEX > ")
            activate_test(file, tid)
        elif ans in data.editor_keys['silent']:
            print("remove a test")
