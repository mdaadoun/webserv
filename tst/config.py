#!/usr/bin/python3
import json

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
    print("generate a json file from test CONFIG")
    print(json.dumps(CONFIG))
    with open("config.json", "w") as file:
        file.write(json.dumps(CONFIG["request"]))
    pass

def generate_file():
    print("Config file generator:")
    ans = input("""
1. generate config.json with question and answers.
2. generate quick default config.json file.
>""")
    create_file()


if __name__ == '__main__':
    generate_file()
