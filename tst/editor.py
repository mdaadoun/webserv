from . import config
from colorama import Fore, Back, Style
from prettytable import PrettyTable


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
        print("""
1. add a test
2. silent/activate a test
3. remove a test
4. quit
""")
        ans = input("default=4 quit > ")
        if ans == "1":
            print("add a test")
        elif ans == "2":
            tid = input("TEST INDEX > ")
            activate_test(file, tid)
        elif ans == "3":
            print("remove a test")
        else:
            editor_running = False
