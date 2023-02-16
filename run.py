#!/usr/bin/python3
import time
import click
import threading

from rich import print
from tst import server, tester, config, editor, data


def run_webserv(testfile):
    print("TEST CPP WEBSERV")
    print("COMPARE PYTHON server and CPP WEBSERV.")

    for test in testfile:
        conf = config.start(test)
        print(conf)
        break #debug
    print("./webserv test")


def run_remote(testfile):
    print("REMOTE SERVER TESTS: (test only 8080 port)")
    print("COMPARE REMOTE SERVER and PYTHON WEBSERV: (only 8080 port tests)")
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


def run_pyserv(testfile):
    print("LOCAL PYTHON SERVER TESTS:")
    for t, test in enumerate(testfile):
        conf = config.start(test)
        if conf is None:
            continue
        else:
            print("\n========================\n", "TEST", t+1, "\n========================")
        server_thread = threading.Thread(target=server.start, args=(conf,))
        server_thread.start()
        while not server.SERVER_RUNNING:
            pass
        time.sleep(0.1)
        if server.SERVER_RUNNING:
            tester.start(conf)
        while server.SERVER_RUNNING:
            pass
        server_thread.join()
        # break #only one test


def run_editor():
    editor.start()

def run_all(testfile):
    print("TODO: all server testing.")

@click.command()
@click.option('-h', '--help', is_flag=True, help='Display help')
@click.option('-e', '--editor', is_flag=True, help='Tests editor')
@click.option('-c', '--conf', is_flag=True, help='Create a json file with questions/answers')
@click.option('-r', '--remote', is_flag=True, help='Run and test remote server')
@click.option('-p', '--pyserv', is_flag=True, help='Run and test the python server')
@click.option('-w', '--webserv', is_flag=True, help='Run and test the cpp server')
@click.option('-a', '--all', is_flag=True, help='Run, test and compare the results of the 3 servers')
def start(help, editor, conf, remote, pyserv, webserv, all):
    with open("tst/tests.txt", "r") as testfile:
        if remote:
            run_remote(testfile)
        elif pyserv:
            run_pyserv(testfile)
        elif webserv:
            run_webserv(testfile)
        elif editor:
            run_editor()
        elif all:
            run_all(testfile)
        elif conf:
            config.generate_file()
        elif help:
            display_help()
        else:
            ## Display menu and run flask web app in a thread
            # run_webapp()
            display_menu()


def display_menu():
    ans = ''
    while ans != '0' and ans != 'q':
        if ans == '1':
            display_help()
        print(data.menu)
        ans = input("\n(default=9) > ")
        print()

def display_help():
    print(data.help)


if __name__ == "__main__":
    print(data.title)
    start()
