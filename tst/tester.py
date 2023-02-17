import requests
from rich import print


def test_get_request(url):
    try:
        response = requests.get(url)
        print("[bold sky_blue2]CLIENT response:[/bold sky_blue2]", response)
        print(response.headers)
        print(response.text)
        # assert response.status_code == port
        # assert response.text == resp
    except requests.exceptions.HTTPError as err:
        print(f'HTTP error occurred: {err}')
    except requests.exceptions.ConnectionError as err:
        print(f'Error Connecting: {err}')
    except requests.exceptions.Timeout as err:
        print(f'Timeout Error: {err}')
    except requests.exceptions.RequestException as err:
        print(f'Error: {err}')


def start(request):
    print("CLIENT IN")
    host = request["host"]
    port = request["port"]
    path = request["path"]
    url = "http://" + host + ":" + port + path
    if request["command"] == "GET":
        print("[bold sky_blue2]CLIENT connection to:[/bold sky_blue2]", url)
        test_get_request(url)
    print("CLIENT OUT")
