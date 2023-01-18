import requests
from rich import print


def test_get_request(add, port, resp):
    try:
        response = requests.get(add)
        print(response)
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
    print("test", CONFIG)
    # Start all the test requests from config
    path = CONFIG
    test_get_request('http://localhost:8000', 200, "Hello, World!")
