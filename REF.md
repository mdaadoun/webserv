
# authorized C functions

## functions used when working with Internet protocols

* **htonl**, **htons**, **ntohl**, **ntohs**
    * https://linux.die.net/man/3/htons

## functions used for managing I/O multiplexing

* **select**
    * https://linux.die.net/man/2/select

* **poll**, function that allows a program to monitor multiple file descriptors
    * https://linux.die.net/man/2/poll

* **epoll**, more recent and efficient version of poll
    * https://linux.die.net/man/4/epoll
    * https://linux.die.net/man/7/epoll

## managing I/O multiplexing, BSD functions

* **kqueue (kqueue, kevent)**
    * https://man.openbsd.org/kqueue.2

## socket interface 

* **socket**, creates an endpoint for communication and returns a descriptor.
    * https://linux.die.net/man/7/socket
    * https://linux.die.net/man/2/socket

...to continue

accept, listen, send, recv, bind, connect,
inet_addr, setsockopt, getsockname, fcntl