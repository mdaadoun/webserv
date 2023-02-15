import socket
from datetime import datetime
from rich import print

SERVER_RUNNING = False

def handle_request(request):
    """Handles the HTTP request."""

    # print("[bold orange_red1]SERVER request:[/bold orange_red1]", request)
    date = datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT")
    headers = {
        'Server': 'pyserv',
        'Date': date,
        'Content-Type': 'text/html',
        # 'Transfer-Encoding': 'chunked',
        # 'Connection': 'keep-alive',
        # 'Content-Encoding': 'gzip'
    }
    content = ''
    status_code = ''

    if request.startswith("GET"):
        header = request.split('\n')[0]
        filename = header.split()[1]
        if filename == '/':
            filename = '/index.html'

        try:
            fin = open('www/html' + filename)
            content = fin.read()
            fin.close()
            status_code = '200 OK'
        except FileNotFoundError:
            status_code = '404 NOT FOUND'
            fin = open('www/html/404.html')
            content = fin.read()
            fin.close()
    else:
        status_code = '400 Bad Request'
    headers_str = "\r\n".join("{}: {}".format(k, v) for k, v in headers.items())
    response = "HTTP/1.1 " + status_code + "\r\n" + headers_str + "\r\n\r\n" + content
    # print('response:', response)
    return response

def start(CONFIG):
    global SERVER_RUNNING
    print("SERVER IN")
    SERVER_HOST = CONFIG["request"]["host"]
    SERVER_PORT = CONFIG["request"]["port"]
    SERVER_RUNNING = True
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        print("[bold orange_red1]SERVER running ok:[/bold orange_red1]", SERVER_HOST + ":" + SERVER_PORT)
        server_socket.bind((SERVER_HOST, int(SERVER_PORT)))
        server_socket.listen(5)
        print('[bold orange_red1]SERVER Listening ok: [/bold orange_red1]%s:%s' % (SERVER_HOST, SERVER_PORT))
        server_socket.settimeout(1)
        while True:
            client_connection, client_address = server_socket.accept()
            print(client_connection, client_address)
            print("[bold orange_red1]SERVER:[/bold orange_red1] connection established.")
            request = client_connection.recv(1024).decode()
            response = handle_request(request)
            client_connection.sendall(response.encode())
            client_connection.close()
            print("[bold orange_red1]SERVER:[/bold orange_red1] close listening.")
            server_socket.close()
            break

    except PermissionError:
        SERVER_RUNNING = False
        print("[bold red]SERVER ERROR: PermissionError")
    except OverflowError:
        SERVER_RUNNING = False
        print("[bold red]SERVER ERROR: OverflowError")
    except OSError:
        SERVER_RUNNING = False
        print("[bold red]SERVER ERROR: OSError (If the port is 8080, the NGINX server is probably running.)")
    SERVER_RUNNING = False
    print("SERVER OUT")
