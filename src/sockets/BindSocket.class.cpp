/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 07:54:03 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/BindSocket.class.hpp"

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int, int, int, int , unsigned long
*  @return  void
*/
BindSocket::BindSocket(int dom, int serv, int protoc, int port, std::string &host):
ISocket(dom, serv, protoc, port, host)
{
	//establish the connection to network and test
	for (int i = 0; i < 6; i++)
	{
		this->_connec = connectToNetwork(this->_sock_fd, this->_addr);
		if (this->_connec == -1)
		{
			if (i != 5)
				std::cerr << "Error: binding (" << errno << " " << strerror(errno) << ")\n";
			else
				testConnection(this->_connec, std::string("Error: name affectation socket."));
		}
		else
			break;
	}
}

/*
*  @brief   Assignment operator.
*           copy other socket in this socket
*  @param   BindSocket &
*  @return  BindSocket &
*/
BindSocket	&BindSocket::operator=(BindSocket const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*  @brief   Method for establish server connection.
*           Set the connection for server
*  @param   int , struct sockaddr_in
*  @return  int
*/
int BindSocket::connectToNetwork(int sock, struct sockaddr_in addr) const
{
	return (bind(sock, (struct sockaddr *)&addr, sizeof(addr)));
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
BindSocket::~BindSocket()
{
}
