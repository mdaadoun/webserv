/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:06:39 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 13:49:55 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.class.hpp"

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
Socket::Socket()
{
}

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket with parameters
*  @param	int , int , int , int , unsigned long
*  @return	void
*/
Socket::Socket(int dom, int serv, int protoc, int port, uint32_t interf)
{
	//set values in address struct for connection
	this->_addr.sin_family = dom;
		//set octets in order for nertwork (htons, htonl)
	this->_addr.sin_port = htons(port);
	this->_addr.sin_addr.s_addr = htonl(interf);
	//establish the socket and test
	this->_sock = socket(dom, serv, protoc);
	testConnection(this->_sock);
	//establish the connection to network and test
	this->_connec = connectToNetwork(this->_sock, this->_addr);
	testConnection(this->_connec);
}

/*
*  @brief	Method for establish connection.
*           set the connection for network
*  @param	int , struct sockaddr_in
*  @return	int
*/
int	Socket::connectToNetwork(int sock, struct sockaddr_in addr)
{
	return (bind(this->_sock, (struct sockaddr *)this->_addr, sizeof(this->_addr)));
}

/*
*  @brief	test _sock or _connec.
*           Confirm  data properly established
*  @param	int
*  @return	void
*/
void	Socket::testConnection(int data)
{
	if (data < 0)
		throw Socket::ErrorConnection();
}

/*
*  @brief	getter for private attribut socket.
*           return the socket associate
*  @param	void
*  @return	int
*/
int	Socket::getSocket() const
{
	return (this->_sock);
}

/*
*  @brief	getter for private attribut connection.
*           return the connection associate
*  @param	void
*  @return	int
*/
int	Socket::getConnection() const
{
	return (this->_connec);
}

/*
*  @brief	getter for private attribut address.
*           return the structur address associate
*  @param	void
*  @return	struct sockaddr_in
*/
struct sockaddr_in	Socket::getAddress() const
{
	return (this->_addr);
}

/*
*  @brief	destructor
*           destroy all member objects
*  @param	void
*  @return	void
*/
Socket::~Socket()
{
}
