"""
 Implements a simple HTTP/1.0 Server
"""

import socket


def handle_request(request):
    """Handles the HTTP request."""

    headers = request.split('\n')
    filename = headers[0].split()[1]
    if filename == '/':
        filename = '/index.html'

    try:
        fin = open('htdocs' + filename)
        content = fin.read()
        fin.close()

        response = 'HTTP/1.0 200 OK\n\n' + content
    except FileNotFoundError:
        response = 'HTTP/1.0 404 NOT FOUND\n\nFile Not Found'

    return response


# Define socket host and port
SERVER_HOST = '0.0.0.0'
SERVER_PORT = 8080

# Create socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((SERVER_HOST, SERVER_PORT))
server_socket.listen(1)
print('Listening on port %s ...' % SERVER_PORT)

while True:
    # Wait for client connections
    client_connection, client_address = server_socket.accept()

    # Get the client request
    request = client_connection.recv(1024).decode()
    print(request)

    # Return an HTTP response
    response = handle_request(request)
    client_connection.sendall(response.encode())

    # Close connection
    client_connection.close()

# Close socket
server_socket.close()
#
# """
#  Implements a simple HTTP/1.0 Server
# """
#
# import socket
#
#
# def handle_request(request):
#     """Handles the HTTP request."""
#
#     headers = request.split('\n')
#     filename = headers[0].split()[1]
#     if filename == '/':
#         filename = '/index.html'
#
#     try:
#         fin = open('htdocs' + filename)
#         content = fin.read()
#         fin.close()
#
#         response = 'HTTP/1.0 200 OK\n\n' + content
#     except FileNotFoundError:
#         response = 'HTTP/1.0 404 NOT FOUND\n\nFile Not Found'
#
#     return response
#
#
# # Define socket host and port
# SERVER_HOST = '0.0.0.0'
# SERVER_PORT = 8080
#
# # Create socket
# server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# server_socket.bind((SERVER_HOST, SERVER_PORT))
# server_socket.listen(1)
# print('Listening on port %s ...' % SERVER_PORT)
#
# while True:
#     # Wait for client connections
#     client_connection, client_address = server_socket.accept()
#
#     # Get the client request
#     request = client_connection.recv(1024).decode()
#     print(request)
#
#     # Return an HTTP response
#     response = handle_request(request)
#     client_connection.sendall(response.encode())
#
#     # Close connection
#     client_connection.close()
#
# # Close socket
# server_socket.close()