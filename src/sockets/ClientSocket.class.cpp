/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 07:52:54 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/ClientSocket.class.hpp"

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int, int, int, int , unsigned long
*  @return  void
*/
ClientSocket::ClientSocket(int dom, int serv, int protoc, int port, std::string &host):
ISocket(dom, serv, protoc, port, host)
{
	//establish the connection to network and test
	this->_connec = connectToNetwork(this->_sock_fd, this->_addr);
	std::cout << _connec << "\n";
	testConnection(this->_connec, std::string("Error: start connection socket."));
}

/*
*  @brief   Assignment operator.
*           copy other socket in this socket
*  @param   ClientSocket &
*  @return  ClientSocket &
*/
ClientSocket	&ClientSocket::operator=(ClientSocket const &rhs)
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
int ClientSocket::connectToNetwork(int sock, struct sockaddr_in addr) const
{
	return (connect(sock, (struct sockaddr *)&addr, sizeof(addr)));
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
ClientSocket::~ClientSocket()
{
}
