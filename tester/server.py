import socket
from rich import print

SERVER_RUNNING = False

def handle_request(request):
    """Handles the HTTP request."""

    print("[bold orange_red1]SERVER request:[/bold orange_red1]", request)
    if request.startswith("GET"):
        headers = request.split('\n')[0]
        filename = headers.split()[1]
        if filename == '/':
            filename = '/index.html'

        try:
            fin = open('htdocs' + filename)
            content = fin.read()
            fin.close()

            response = 'HTTP/1.0 200 OK\n\n' + content
        except FileNotFoundError:
            response = 'HTTP/1.0 404 NOT FOUND\n\nFile Not Found'
    else:
        response = 'HTTP/1.1 400 Bad Request\n\n'

    return response


def start(CONFIG):
    global SERVER_RUNNING
    SERVER_HOST = CONFIG["request"]["host"]
    SERVER_PORT = CONFIG["request"]["port"]
    SERVER_RUNNING = True
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        print("[bold orange_red1]SERVER running:[/bold orange_red1]", SERVER_HOST + ":" + SERVER_PORT)
        server_socket.bind((SERVER_HOST, int(SERVER_PORT)))
        server_socket.listen(1)
        # print('SERVER: Listening on port %s:%s' % (SERVER_HOST, SERVER_PORT))
        # server_socket.settimeout(1)
        # while True:
        client_connection, client_address = server_socket.accept()
        # print(client_connection, client_address)
        print("[bold orange_red1]SERVER:[/bold orange_red1] connection established.")
        request = client_connection.recv(1024).decode()
        response = handle_request(request)
        client_connection.sendall(response.encode())
        client_connection.close()
        print("[bold orange_red1]SERVER:[/bold orange_red1] close listening.")
        server_socket.close()
            # break
    except PermissionError:
        SERVER_RUNNING = False
        print("[bold red]SERVER ERROR: PermissionError")
    except OverflowError:
        SERVER_RUNNING = False
        print("[bold red]SERVER ERROR: OverflowError")
    SERVER_RUNNING = False
