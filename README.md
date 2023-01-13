# Webserv

## Documentation

* https://developer.mozilla.org/en-US/docs/Web/HTTP
  * https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Evolution_of_HTTP

* https://fr.wikipedia.org/wiki/Hypertext_Transfer_Protocol
  * https://www.w3.org/Protocols/
  * https://www.rfc-editor.org/rfc/rfc2616

* https://en.wikipedia.org/wiki/Common_Gateway_Interface

## Steps for the mandatory part

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
>* I propose python:
>  *  ```python3 test.py```
* [ ] unit-test / assert along dev
  * many libraries in python: requests, httplib2, treq, httpretty

## Bonus ?

* Support cookies and session management (prepare quick examples).
* Handle multiple CGI.

