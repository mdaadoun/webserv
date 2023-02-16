/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISocket.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:37:07 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/14 11:17:00 by tlafont          ###   ########.fr       */
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
typedef	unsigned long		u_long;

// class interface
class ISocket
{
	public:
	    //---- canonical form ----//
			// constructors //
				// overload constructor
		ISocket(int dom, int serv, int protoc, int port, u_long interf);
			// destructor //
	    virtual ~ISocket(void);
			
	    //---- getter methods ----//
		int					getSocketFd() const;
		int					getConnection() const;
		struct sockaddr_in	getAddress() const;

	    //---- member methods ----//
				// virtual function to connect to a network
				//(at define for a bindSocket or a listenSocket)
		virtual int	connectToNetwork(int sock, struct sockaddr_in addr) const = 0;

				// connection test establishment
		void	testConnection(int to_test);

		//---- exception class ----//
		class ErrorConnection : public std::exception
		{
			public:
				char const	*what() const throw();
		};
	protected:
		int					_sock_fd;
		int					_connec;
		struct sockaddr_in	_addr;

	private:
    	ISocket(void);
	    ISocket(const ISocket& rhs);
	    ISocket  &operator=(const ISocket& rhs);
};

#endif
