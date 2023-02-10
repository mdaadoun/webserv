/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:37:07 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 13:50:14 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SOCKET_HPP
#define SOCKET_HPP

// Includes

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <exception>

// Typedefs

typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;

// class interface
class Socket
{
	public:
	    //---- canonical form ----//
			// constructors //
				// default constructor
		Socket(int dom, int serv, int protoc, int port, uint32_t interf);
			// destructor //
	    ~Socket(void);
			
	    //---- getter methods ----//
		int					getSocket() const;
		int					getConnection() const;
		struct sockaddr_in	getAddress() const;

	    //---- member methods ----//
				// virtual function to connect to a network
				//(at define for a server or a client)
		int	connectToNetwork(int sock, struct sockaddr_in addr);

				// connection test establishment
		void	testConnection(int to_test);

			// exception class//
		class ErrorConnection : std::exception
		{
			public:
				char const	*what() const throw();
		};
	//    int connect();
	//    int listen();
	//    int bind();
	//    int recv();
	//    int send();
	//    int setSockOpt();
	//    int getSockOpt();
	private:
		int					_sock;
		int					_connec;
		struct sockaddr_in	_addr;

    	Socket(void);
	    Socket(const Socket& s);
	    Socket  &operator=(const Socket& s);
};

#endif
