import requests
import time
from rich import print


def test_get_request(add):
    try:
        response = requests.get(add)
        print("[bold sky_blue2]CLIENT response:[/bold sky_blue2]", response)
        # print(response.json())
        print(response.status_code)
        print(response.headers)
        print(response.text)
        print(response.raw)
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


def start(CONFIG):
    # Start all the test requests from config
    path = CONFIG
    address = "http://" + CONFIG["request"]["host"] + ":" + CONFIG["request"]["port"] + CONFIG["request"]["path"]
    if CONFIG["request"]["command"] == "GET":
        print("[bold sky_blue2]CLIENT connection to:[/bold sky_blue2]", address)
        test_get_request(address)
