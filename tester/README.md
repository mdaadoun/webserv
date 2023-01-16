# TODO

* tester python, unit test to compare result from
    * mock config.ini files (default will test ./webserv <FILE> with a generated file.ini)
        * ```python3 run.py```
    * NGINX’s server (on VM).
        * ```python3 run.py -n```
    * prototype python HTTP server.
        * ```python3 run.py -p```
    * the 3 are compared, test by test
        * ```python3 run.py -a```

* [ ] unit-test / assert along dev
* many libraries in python: requests, httplib2, treq, httpretty


## Doc
* https://requests.readthedocs.io/en/latest/user/quickstart
* https://docs.python.org/3/library/socket.html

## server.py: simple server
* run.py arguments
* run and call a simple server.py
* https://www.codementor.io/@joaojonesventura/building-a-basic-http-server-from-scratch-in-python-1cedkg0842
* https://medium.com/swlh/build-web-server-from-scratch-with-python-60188f3b162a
* https://bhch.github.io/posts/2017/11/writing-an-http-server-from-scratch/

## genini.py: generate config.ini files for testings

## tester.py: request unit testing
* call the nginx server from VM
* https://www.geeksforgeeks.org/unit-testing-python-unittest/
* https://stackoverflow.com/questions/9559963/unit-testing-a-python-app-that-uses-the-requests-library
* https://cra.mr/2014/05/20/mocking-requests-with-responses/

## cgi programming
* https://www.geeksforgeeks.org/what-is-cgi-in-python/
* https://www.geeksforgeeks.org/cgi-programming-python/