# TODO

* get the same result from nginx to pyserv
* [ ] unit-test / assert along dev
```
* exemple http
GET /about.html HTTP/1.0
User-Agent: Mozilla/5.0
* exemple 2
POST /form.php HTTP/1.0
Content-Type: application/x-www-form-urlencoded
Content-Length: 21

name=John&surname=Doe

* connection, question/answer example once connected to google.com on port 80
(1)
GET /about/ HTTP/1.0

(2)
HTTP/1.0 200 OK
Vary: Accept-Encoding
Content-Type: text/html
Date: Thu, 09 Feb 2017 16:41:37 GMT
Expires: Thu, 09 Feb 2017 16:41:37 GMT
Cache-Control: private, max-age=0
Last-Modified: Thu, 08 Dec 2016 01:00:57 GMT
X-Content-Type-Options: nosniff
Server: sffe
X-XSS-Protection: 1; mode=block
Accept-Ranges: none
<!DOCTYPE html>
    <html class="google mmfb" lang="en">
        <head>
        ...

</html>
Connection closed by foreign host.
```

## Doc
* https://requests.readthedocs.io/en/latest/user/quickstart
* https://docs.python.org/3/library/socket.html

## Resources
* WEB and HTTP introduction:
1. https://www.youtube.com/watch?v=ZT8uqIEG92o
2. https://www.youtube.com/watch?v=RDvlb_XgVyI
3. https://www.youtube.com/watch?v=Q5YIrYkrVXg
4. https://www.youtube.com/watch?v=Fxgw_BxZg2I
5. https://www.youtube.com/watch?v=PNt8zXl7EJ0  

## server.py: simple server
* run.py arguments
* run and call a simple server.py
* https://www.codementor.io/@joaojonesventura/building-a-basic-http-server-from-scratch-in-python-1cedkg0842
* https://medium.com/swlh/build-web-server-from-scratch-with-python-60188f3b162a
* https://bhch.github.io/posts/2017/11/writing-an-http-server-from-scratch/

## genini.py: generate config.ini files for testings

## tester.py: request unit testing
* https://www.geeksforgeeks.org/unit-testing-python-unittest/
* https://stackoverflow.com/questions/9559963/unit-testing-a-python-app-that-uses-the-requests-library
* https://cra.mr/2014/05/20/mocking-requests-with-responses/

## cgi programming
* https://www.geeksforgeeks.org/what-is-cgi-in-python/
* https://www.geeksforgeeks.org/cgi-programming-python/