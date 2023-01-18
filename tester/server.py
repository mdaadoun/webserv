import socket

SERVER_RUNNING = False

def handle_request(request):
    """Handles the HTTP request."""

    # headers = request.split('\n')
    # filename = headers[0].split()[1]
    # if filename == '/':
    #     filename = '/index.html'
    #
    # try:
    #     fin = open('htdocs' + filename)
    #     content = fin.read()
    #     fin.close()
    #
    #     response = 'HTTP/1.0 200 OK\n\n' + content
    # except FileNotFoundError:
    #     response = 'HTTP/1.0 404 NOT FOUND\n\nFile Not Found'

    if request.startswith("GET"):
        response = 'HTTP/1.0 200 OK\n\nHello World'
    else:
        response = 'HTTP/1.1 400 Bad Request\n\n'

    return response


def start(CONFIG):
    global SERVER_RUNNING
    SERVER_HOST = CONFIG["request"]["host"]
    SERVER_PORT = int(CONFIG["request"]["port"])
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        print(SERVER_HOST, SERVER_PORT)
        server_socket.bind((SERVER_HOST, SERVER_PORT))
        server_socket.listen(1)
        SERVER_RUNNING = True
        print('Listening on port %s:%s' % (SERVER_HOST, SERVER_PORT))

        while True:
            client_connection, client_address = server_socket.accept()
            request = client_connection.recv(1024).decode()
            print("connection established")
            print(request)
            response = handle_request(request)
            client_connection.sendall(response.encode())
            client_connection.close()
            break
    except PermissionError:
        print("PermissionError")
    server_socket.close()
    SERVER_RUNNING = False
