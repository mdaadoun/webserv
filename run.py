import time

import click
import threading
from rich import print
from tester import server, tester, genini

@click.command()
@click.option('-n', '--_nginx', is_flag=True, help='Run and test nginx server')
@click.option('-p', '--_python', is_flag=True, help='Run and test the python server')
@click.option('-a', '--_all', is_flag=True, help='Run and test the 3 servers')
def start(_nginx, _python, _all):
    tests = open("tester/tests.txt", "r")
    if _nginx:
        t = 1
        for test in tests:
            CONFIG = genini.start(test)
            if CONFIG is None or CONFIG["request"]["port"] != "8080":
                continue
            else:
                print("\n========================\n", "TEST", t, "\n========================")
                t += 1
            time.sleep(1)
            tester.start(CONFIG)

    elif _python:
        t = 1
        for test in tests:
            CONFIG = genini.start(test)
            if CONFIG is None:
                continue
            else:
                print("\n========================\n", "TEST", t, "\n========================")
                t += 1
            server_thread = threading.Thread(target=server.start, args=(CONFIG,))
            server_thread.start()
            while not server.SERVER_RUNNING:
                pass
            time.sleep(1)
            if server.SERVER_RUNNING:
                tester.start(CONFIG)
            while server.SERVER_RUNNING:
                pass
            server_thread.join()
            # break
    elif _all:
        print("_all")
        click.echo(f"Hello, {_all}!")
    else:
        print("./webserv test")

def display_help():
    print("""Tester usage:
    * default: will test ./webserv <CONFIG_FILE> with generated config files
        * [bold magenta]python3 run.py[/bold magenta]
    * -n: NGINX’s server (on VM).
        * [bold magenta]python3 run.py -n[/bold magenta]
    * -p: prototype python HTTP server.
        * [bold magenta]python3 run.py -p[/bold magenta]
    * -a: the 3 are compared, test by test
        * [bold magenta]python3 run.py -a[/bold magenta]""")

if __name__ == "__main__":
    display_help()
    start()
