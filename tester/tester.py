import requests


def test_get_request():
    response = requests.get('http://localhost:8000')
    assert response.status_code == 200
    assert response.text == "Hello, World!"


def test_invalid_request():
    response = requests.get('http://localhost:8000/invalid')
    assert response.status_code == 400


def start(CONFIG):
    print("test", CONFIG)
    test_get_request()
    test_invalid_request()
