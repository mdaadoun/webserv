/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 15:48:09 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BindSocket.class.hpp"

/*
*  @brief   Default constructor of the class BindSocket.
*           Initialize the socket without any parameters
*  @param   void
*  @return  void
*/
BindSocket::BindSocket()
{
}

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int, int, int, int , unsigned long
*  @return  void
*/
BindSocket(int dom, int serv, int protoc, int port, u_long interf) : ISocket(dom, serv, protoc, port, interf)
{
	//establish the connection to network and test
	this->_connec = connectToNetwork(this->_sock_fd, this->_addr);
	testConnection(this->_connec);
}

/*
*  @brief   Copy constructor of the class BindSocket.
*           Initialize the socket with other BindSocket
*  @param   BindSocket &
*  @return  void
*/
BindSocket::BindSocket(BindSocket const &rhs)
{
	*this = rhs;
}

/*
*  @brief   Assignment operator.
*           copy other socket in this socket
*  @param   BindSocket &
*  @return  void
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
int BindSocket::connectToNetwork(int sock, struct sockaddr_in addr)
{
	return (bind(this->_sock_fd, (struct sockaddr *)this->_addr, sizeof(this->_addr)));
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
