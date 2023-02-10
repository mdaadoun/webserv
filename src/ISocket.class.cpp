/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISocket.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:06:39 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 15:47:55 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ISocket.class.hpp"

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
ISocket::ISocket()
{
}

/*
*  @brief	Overload constructor of the class ISocket.
*           Initialize the socket with parameters
*  @param	int , int , int , int , unsigned long
*  @return	void
*/
ISocket::ISocket(int dom, int serv, int protoc, int port, u_long interf)
{
	//set values in address struct for connection
	this->_addr.sin_family = dom;
		//set octets in order for nertwork (htons, htonl)
	this->_addr.sin_port = htons(port);
	this->_addr.sin_addr.s_addr = htonl(interf);
	//establish the socket and test
	this->_sock_fd = socket(dom, serv, protoc);
	testConnection(this->_sock_fd);
}

/*
*  @brief	Copy  constructor.
*           Initialize the socket with other socket
*  @param	ISocket &
*  @return	void
*/
ISocket::ISocket(const ISocket& rhs)
{
	*this = rhs;
}

/*
*  @brief	Assignment operator.
*           Copy other socket in this socket
*  @param	ISocket
*  @return	Isocket &
*/
ISocket  &ISocket::operator=(const ISocket& rhs)
{
	(void)rhs;
	return (*this);
}

/*
*  @brief	Test _sock_fd or _connec.
*           Confirm  data properly established
*  @param	int
*  @return	void
*/
void	ISocket::testConnection(int data)
{
	if (data < 0)
		throw ISocket::ErrorConnection();
}

/*
*  @brief	Getter for private attribut socket.
*           Return the socket associate
*  @param	void
*  @return	int
*/
int	ISocket::getSocket() const
{
	return (this->_sock_fd);
}

/*
*  @brief	Getter for private attribut connection.
*           Return the connection associate
*  @param	void
*  @return	int
*/
int	ISocket::getConnection() const
{
	return (this->_connec);
}

/*
*  @brief	Getter for private attribut address.
*           Return the structur address associate
*  @param	void
*  @return	struct sockaddr_in
*/
struct sockaddr_in	ISocket::getAddress() const
{
	return (this->_addr);
}

/*
*  @brief	Destructor
*           Destroy all member objects
*  @param	void
*  @return	void
*/
ISocket::~ISocket()
{
}
