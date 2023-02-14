/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/13 11:43:56 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sockets/ClientSocket.class.hpp"

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int, int, int, int , unsigned long
*  @return  void
*/
ClientSocket::ClientSocket(int dom, int serv, int protoc, int port, u_long interf):
ISocket(dom, serv, protoc, port, interf)
{
	//establish the connection to network and test
	this->_connec = connectToNetwork(this->_sock_fd, this->_addr);
	std::cout << _connec << "\n";
	testConnection(this->_connec);
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