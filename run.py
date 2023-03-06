#!/usr/bin/python3
import time
import click
import threading
import subprocess

from rich import print
from tst import server, tester, config, editor, data


def run_webserv(testfile):
    print("TEST CPP WEBSERV")

    for t, test in enumerate(testfile):
        print("./webserv confile")
        test_data = config.prepare_test(test, 'webserv')
        if test_data is None:
            continue
        program = "./webserv"
        confile = ''
        with open("tst/config.txt", "r") as cf:
            confile = cf.readline()
        subprocess.Popen([program, confile])
        time.sleep(0.1)
        tester.start(test_data, t)
        time.sleep(0.1)


def run_remote(testfile):
    print("REMOTE SERVER TESTS:")
    for t, test in enumerate(testfile):
        test_data = config.prepare_test(test, 'remote')
        if test_data is None:
            continue
        else:
            print("\n========================\n", "TEST", t + 1, "\n========================")
            # time.sleep(0.1)
            tester.start(test_data, t)


def run_pyserv(testfile):
    print("LOCAL PYTHON SERVER TESTS:")
    for t, test in enumerate(testfile):
        test_data = config.prepare_test(test)
        if test_data is None:
            continue
        else:
            print("\n========================\n", "TEST", t + 1, "\n========================")
            server_thread = threading.Thread(target=server.start, args=(test_data,))
            server_thread.start()
            while not server.SERVER_RUNNING:
                pass
            time.sleep(0.1)
            if server.SERVER_RUNNING:
                tester.start(test_data, t)
            while server.SERVER_RUNNING:
                pass
            server_thread.join()
            # break #only one test


def run_test_editor():
    editor.start()


def run_config_editor():
    config.editor()


@click.command()
@click.option('-h', '--help', is_flag=True, help='Display help')
@click.option('-e', '--editor', is_flag=True, help='Tests editor')
@click.option('-c', '--conf', is_flag=True, help='Create a json file with questions/answers')
@click.option('-r', '--remote', is_flag=True, help='Run and test remote server')
@click.option('-p', '--pyserv', is_flag=True, help='Run and test the python server')
@click.option('-w', '--webserv', is_flag=True, help='Run and test the cpp server')
def start(help, editor, conf, remote, pyserv, webserv):
    with open("tst/tests.txt", "r") as testfile:
        if remote:
            run_remote(testfile)
        elif pyserv:
            run_pyserv(testfile)
        elif webserv:
            run_webserv(testfile)
        elif editor:
            run_test_editor()
        elif conf:
            run_config_editor()
        elif help:
            display_help()
        else:
            display_menu()


def display_menu():
    ans = ''
    while ans not in data.menu_keys['exit']:
        print(data.menu)
        ans = input("\n(default=webserv) > ")
        if ans in data.menu_keys['help']:
            display_help()
        elif ans in data.menu_keys['editor']:
            run_test_editor()
        elif ans in data.menu_keys['config']:
            run_config_editor()
        elif ans in data.menu_keys['remote']:
            with open("tst/tests.txt", "r") as testfile:
                run_remote(testfile)
        elif ans in data.menu_keys['pyserv']:
            with open("tst/tests.txt", "r") as testfile:
                run_pyserv(testfile)
        elif ans in data.menu_keys['webserv'] or ans.strip() == '':
            with open("tst/tests.txt", "r") as testfile:
                run_webserv(testfile)
        print()


def display_help():
    print(data.help)


if __name__ == "__main__":
    print(data.title)
    start()
