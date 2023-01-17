CONFIG = {
    "host": "0.0.0.0",
    "port": "80"
}


def start(config):
    input = config.split(":")[0]
    output = config.split(":")[1]
    CONFIG["host"] = input.split(",")[2]
    CONFIG["port"] = input.split(",")[3]
    return CONFIG

# generate a config.ini file for ./webserv to try
def create_file():
    pass
