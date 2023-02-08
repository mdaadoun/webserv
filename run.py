#!/usr/bin/python3.8
import time
import click
import threading
from rich import print
from tst import server, tester, config


@click.command()
@click.option('-n', '--remote', is_flag=True, help='Run and test remote server')
@click.option('-p', '--python', is_flag=True, help='Run and test the python server')
@click.option('-w', '--webserv', is_flag=True, help='Run and test the cpp server')
@click.option('-a', '--all', is_flag=True, help='Run, test and compare the results of the 3 servers')
def start(remote, python, webserv, all):
    tests = open("tst/tests.txt", "r")
    if remote:
        print("REMOTE SERVER TESTS: (test only 8080 port)")
        t = 1
        for test in tests:
            CONFIG = config.start(test)
            if CONFIG is None or CONFIG["request"]["port"] != "8080":
                continue
            else:
                print("\n========================\n", "TEST", t, "\n========================")
                t += 1
            time.sleep(1)
            tester.start(CONFIG)

    elif python:
        print("LOCAL PYTHON SERVER TESTS:")
        t = 1
        for test in tests:
            CONFIG = config.start(test)
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
    elif webserv:
        print("TEST CPP WEBSERV")
        print("./webserv test")
    elif all:
        print("COMPARE REMOTE SERVER, PYTHON WEBSERV and CPP WEBSERV: (only 8080 port)")
        click.echo(f"Hello, {_all}!")
    else:
        display_help()


def display_help():
    print("""[bold yellow]
=============
Tester usage:
=============
[/bold yellow]
    * [bold yellow]default[/bold yellow] (./run.py) without option display this help.
    
    * [bold yellow]cpp webserv[/bold yellow]: 
        will test [bold green]CPP WEBSERV[/bold green] with ./webserv <CONFIG_FILE>
            * [bold magenta]./run.py -w or --webserv[/bold magenta]
    
    * [bold yellow]remote server[/bold yellow]: 
        will test [bold green]REMOTE[/bold green] server (NGINX’s server if possible).
            * [bold magenta]./run.py -r or --remote[/bold magenta]
    
    * [bold yellow]local python server[/bold yellow]: 
        will test local [bold green]PYTHON[/bold green] HTTP web server.
            * [bold magenta]./run.py -p or --python[/bold magenta]
    
    * [bold yellow]all servers[/bold yellow]: 
        will test the 3 servers [bold green](REMOTE, PYTHON and CPP)[/bold green] and results are compared.
            * [bold magenta]./run.py -a or --all[/bold magenta]
    
    * notes:
        [italic]* for ./webserv the tester will generate multiple config files.
        * add tests to ./tst/tests.txt. (The request:The response expected)
        * for remote and the --all option, only the tests with 8080 port will be tested.[/italic]""")


if __name__ == "__main__":
    start()
