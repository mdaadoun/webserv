#pragma once
#ifndef SOCKET_HPP
#define SOCKET_HPP

// Includes

#include <iostream>

// Typedefs

typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;


class Socket {
public:
    // Constructor and Destructor
    Socket(void);
    ~Socket(void);

    // methods
    inline int		getFd(void) { return (this->_fd); }

//    int connect();
//    int listen();
//    int bind();
//    int recv();
//    int send();
//    int setSockOpt();
//    int getSockOpt();

private:
    Socket(const Socket& s);
    Socket  &operator=(const Socket& s);

    int _fd;
};

#endif