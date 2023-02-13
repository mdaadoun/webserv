#!/usr/bin/python3.8
import time
import click
import threading
from rich import print
from tst import server, tester, config


def run_webserv(testfile):
    print("TEST CPP WEBSERV")

    for test in testfile:
        conf = config.start(test)
        print(conf)
        break #debug
    print("./webserv test")


def run_remote(testfile):
    print("REMOTE SERVER TESTS: (test only 8080 port)")
    t = 1
    for test in testfile:
        conf = config.start(test)
        if conf is None or conf["request"]["port"] != "8080":
            continue
        else:
            print("\n========================\n", "TEST", t, "\n========================")
            t += 1
        time.sleep(1)
        tester.start(conf)


def run_python_server(testfile):
    print("LOCAL PYTHON SERVER TESTS:")
    t = 1
    for test in testfile:
        conf = config.start(test)
        if conf is None:
            continue
        else:
            print("\n========================\n", "TEST", t, "\n========================")
            t += 1
        server_thread = threading.Thread(target=server.start, args=(conf,))
        server_thread.start()
        while not server.SERVER_RUNNING:
            pass
        time.sleep(1)
        if server.SERVER_RUNNING:
            tester.start(conf)
        while server.SERVER_RUNNING:
            pass
        server_thread.join()


def run_all(testfile):
    print("COMPARE REMOTE SERVER, PYTHON WEBSERV and CPP WEBSERV: (only 8080 port)")
    click.echo(f"Hello, {all}!")


@click.command()
@click.option('-h', '--help', is_flag=True, help='Create a json file with questions/answers')
@click.option('-c', '--conf', is_flag=True, help='Create a json file with questions/answers')
@click.option('-n', '--remote', is_flag=True, help='Run and test remote server')
@click.option('-p', '--python', is_flag=True, help='Run and test the python server')
@click.option('-w', '--webserv', is_flag=True, help='Run and test the cpp server')
@click.option('-a', '--all', is_flag=True, help='Run, test and compare the results of the 3 servers')
def start(help, conf, remote, python, webserv, all):
    with open("tst/tests.txt", "r") as testfile:
        if remote:
            run_remote(testfile)
        elif python:
            run_python_server(testfile)
        elif webserv:
            run_webserv(testfile)
        elif all:
            run_all(testfile)
        elif conf:
            config.generate_file()
        elif help:
            display_help()
        else:
            display_help()


def display_help():
    print("""[bold yellow]
=============
Tester usage:
=============
[/bold yellow]
    * [bold yellow]default[/bold yellow] (./run.py) without option display this help. 
        * [italic](option -h and --help will work too)[/italic]
    
    * [bold yellow]config file[/bold yellow]: 
        will generate a [bold green]config.json[/bold green] file with default or manual questions/answers parameters.
            * [bold magenta]./run.py -c or --conf[/bold magenta]
    
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
        * for remote and the --all option, only the tests with 8080 port will be tested.[/italic]
""")


if __name__ == "__main__":
    start()
