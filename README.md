# Webserv

## Documentation

* https://en.wikipedia.org/wiki/Web_server

### the http protocol
* https://developer.mozilla.org/en-US/docs/Web/HTTP
  * https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Evolution_of_HTTP

* https://fr.wikipedia.org/wiki/Hypertext_Transfer_Protocol
  * https://www.w3.org/Protocols/
    * 1.0 : https://www.w3.org/Protocols/HTTP/1.0/spec.html
    * 1.1 : https://www.rfc-editor.org/rfc/rfc9112.html
      * https://www.rfc-editor.org/rfc/rfc2616

### others important topics
* https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers
* https://en.wikipedia.org/wiki/Network_socket
* https://en.wikipedia.org/wiki/Common_Gateway_Interface

## Steps for the mandatory part

1. start with building a simple http server with blocking fds at first just to get familiar with sockets.
2. parse the request and build the response it is important to understand the rules that they follow.
  * https://www.rfc-editor.org/rfc/rfc9112.html
3. Once you are able to display an html in the browser using your server start adding other features on top:
   * Non-blocking fds and all the multiplexing logic (epoll/kqueue/poll/select).
   * Implement config file and all the location logic.
   * CGI (which is basically a program that takes a script as argument as well as required environment variables (check CGI RFC) and reads from standard input to print a message to standard output and perform other actions (like file saving).
   * Start adding  GET, POST and DELETE logic.
   * Testing the requirements of the project.

### structuring program, parsing functions
* [ ] extract information from configuration file (parsing, fstream ?)
    * [ ] parse and validate the config.ini
      * https://en.wikipedia.org/wiki/INI_file
        * [ ] get the port number to listen on
        * [ ] the root directory for serving files

### implementing network features
* [ ] creating a socket to listen for incoming connections
  * [ ] setting library that provides networking functions
    > * **Any external library and Boost libraries are forbidden.**
    >  * For reference only:
    >     * https://www.boost.org/doc/libs/1_76_0/doc/html/boost_asio.html
    >     * https://en.wikipedia.org/wiki/Berkeley_sockets

### implementing HTTP protocol and its request/response structure.
* [ ] parsing incoming HTTP requests
  * [ ] get the request method, URI and headers.
* [ ] generating appropriate HTTP responses
  * [ ] read and send the file requested, deliver an html web page
  > * **You must be able to serve a fully static website.**

### tester
> Do not test with only one program. Write your tests with a more
  convenient language such as Python or Golang, and so forth. Even in
  C or C++ if you want to.
>* Go for python then :)
```
  > python3 -m venv venv
  > source venv/bin/activate
  > pip install -r requirements.txt
  > python3 run.py [default webserv tests][-p, python server tests][-n, nginx server tests][-a, all tests]
```
* The tester can be used for fast checking during dev, it need to be tested with a browser.

### Notes on Git Fork/Pull Request/Merge

## Bonus ?

* Support cookies and session management (prepare quick examples).
* Handle multiple CGI.

