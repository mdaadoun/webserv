import click
from tester import server, tester, genini

@click.command()
@click.option('-n', '--_nginx', is_flag=True, help='Run and test nginx server')
@click.option('-p', '--_python', is_flag=True, help='Run and test the python server')
@click.option('-a', '--_all', is_flag=True, help='Run and test the 3 servers')
def start(_nginx, _python, _all):
    tests = open("tester/tests.txt", "r")
    if _nginx:
        print("test nginx server")
        click.echo(f"Hello, {_nginx}!")
    if _python:
        for test in tests:
            CONFIG = genini.start(test)
            server.start(CONFIG)
        #     tester.start(CONFIG)
    if _all:
        print("_all")
        click.echo(f"Hello, {_all}!")
    else:
        print("./webserv test")

def display_help():
    print("""
* unit tester python, OPTIONS:
    * default: will test ./webserv <CONFIG_FILE> with generated config files
        * python3 run.py
    * -n: NGINX’s server (on VM).
        * python3 run.py -n
    * -p: prototype python HTTP server.
        * python3 run.py -p
    * -a: the 3 are compared, test by test
        * python3 run.py -a
    """)

if __name__ == "__main__":
    display_help()
    start()
