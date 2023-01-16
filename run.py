from tester import server, tester, genini

# temporary, then get it from config.ini generator
SERVER_HOST = '0.0.0.0'
SERVER_PORT = 8000


def start():
    genini.start()  # will replace global and return config as data
    server.start(SERVER_PORT)
    tester.start(SERVER_HOST, SERVER_PORT)


if __name__ == "__main__":
    start()
