import requests
from rich import print


def check_response(tst, res):
    for t in tst:
        if t == "Status":
            print("STATUS:", end='')
            if str(tst[t]) == str(res.status_code):
                print("[green]OK[/green] ", end='')
            else:
                print("[red]NO[/red] ", end='')
        else:
            print(t.upper() + ':', end='')
            try:
                if tst[t] == '':
                    if len(res.headers[t]):
                        print("[green]OK[/green] ", end='')
                elif tst[t] == res.headers[t]:
                    print("[green]OK[/green] ", end='')
                else:
                    print("[red]NO[/red] ", end='')
            except KeyError:
                print("[red]NO[/red] ", end='')
    print()


def get_response(url):
    try:
        response = requests.get(url)
        return response
    except requests.exceptions.HTTPError as err:
        print(f'HTTP error occurred: {err}')
    except requests.exceptions.ConnectionError as err:
        print(f'Error Connecting: {err}')
    except requests.exceptions.Timeout as err:
        print(f'Timeout Error: {err}')
    except requests.exceptions.RequestException as err:
        print(f'Error: {err}')


def get_url(r):
    host = r["request"]["host"]
    port = r["request"]["port"]
    path = r["request"]["path"]
    return "http://" + host + ":" + port + path


def start(test, t):
    if test["request"]["command"] == "GET":
        url = get_url(test)
        print("[bold sky_blue2]CLIENT connection to:[/bold sky_blue2]", url)
        response = get_response(url)
        if response.headers:
            print("[bold sky_blue2]CLIENT response:[/bold sky_blue2]", response)
            check_response(test['response'], response)
