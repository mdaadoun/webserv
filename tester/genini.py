CONFIG = {
    "request": {
        "command": "GET",
        "path": "/",
        "host": "0.0.0.0",
        "port": "80",
        "protocol": "HTTP/1.1"
    },
    "response": {}
}


def start(config):
    input = config.split(":")[0]
    if input[0][0] == "#":
        return None
    output = config.split(":")[1]
    conf = input.split(",")
    CONFIG["request"]["command"] = conf[0]
    CONFIG["request"]["path"] = conf[1]
    CONFIG["request"]["host"] = conf[2]
    CONFIG["request"]["port"] = conf[3]
    CONFIG["request"]["protocol"] = conf[4]
    return CONFIG


# generate a config.ini file for ./webserv <FILE>
def create_file():
    pass
