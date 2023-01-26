# authorized C functions

## socket interface programming

* **socket** - creates an endpoint for communication and returns a descriptor.
    * https://linux.die.net/man/7/socket
    * https://linux.die.net/man/2/socket
    * https://fr.manpages.org/socket/7

* **setsockopt** - set the socket options
  * https://fr.manpages.org/setsockopt/2
  * https://linux.die.net/man/3/setsockopt

* **getsockname** - get the socket name
  * https://linux.die.net/man/3/getsockname
  * https://fr.manpages.org/getsockname/2

* **accept** - accept a connection on a socket
  * https://linux.die.net/man/2/accept
  * https://fr.manpages.org/accept/2

* **listen** - listen for connections on a socket
  * https://linux.die.net/man/2/listen
  * https://fr.manpages.org/listen/2

* **send** - send a message on a socket
  * https://fr.manpages.org/send/2
  * https://linux.die.net/man/2/send

* **recv** - receive a message from a socket
  * https://fr.manpages.org/recv/2
  * https://linux.die.net/man/2/recv

* **bind** - bind a name to a socket
  * https://linux.die.net/man/2/bind
  * https://fr.manpages.org/bind/2

* connect - initiate a connection on a socket
  * https://linux.die.net/man/2/connect
  * https://fr.manpages.org/connect/2


## managing I/O multiplexing

* **select**
    * https://linux.die.net/man/2/select
    * https://fr.manpages.org/select/2

* **poll**, function that allows a program to monitor multiple file descriptors
    * https://linux.die.net/man/2/poll

* **epoll**, more recent and efficient version of poll
    * https://linux.die.net/man/4/epoll
    * https://linux.die.net/man/7/epoll
    * **epoll_create**
      * https://fr.manpages.org/epoll_create1/2
    * **epoll_ctl**
      * https://fr.manpages.org/epoll_ctl/2
    * **epoll_wait**
      * https://fr.manpages.org/epoll_wait/2

## managing I/O multiplexing, BSD functions

* **kqueue (kqueue, kevent)**
    * https://man.openbsd.org/kqueue.2

## functions used when working with Internet protocols (converting 16 and 32 bit integer)

* **htonl**, **htons**, **ntohl**, **ntohs**
    * https://linux.die.net/man/3/htons

---

* inet_addr - Internet address manipulation routines
  * https://linux.die.net/man/3/inet_addr

* getprotobyname - get protocol entry
  * https://linux.die.net/man/3/getprotobyname
  * https://fr.manpages.org/getprotobyname_r/3

* fcntl - file control
  * https://linux.die.net/man/3/fcntl

* getaddrinfo - network address and service translation
  * https://linux.die.net/man/3/getaddrinfo

* freeaddrinfo
  * https://linux.die.net/man/3/freeaddrinfo

* execve
* dup
* dup2
* pipe
* strerror
* gai_strerror
* errno
* fork
