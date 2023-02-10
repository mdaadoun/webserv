/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:06:39 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 13:18:27 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.class.hpp"

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
Socket::Socket() {};

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket with parameters
*  @param	int , int , int , int , unsigned long
*  @return	void
*/
Socket::Socket(int dom, int serv, int protoc, int port, uint32_t interf)
{
	//set values in address struct for connection
	this->_address.sin_family = dom;
		//set octets in order for nertwork (htons, htonl)
	this->_address.sin_port = htons(port);
	this->_address.sin_addr.s_addr = htonl(interf);
	//establish the socket and test
	this->_sock = socket(dom, serv, protoc);
	testConnection(this->_sock);
	//establish the connection to network and test
	this->_connection = connectToNetwork(this->_sock, this->_address);
	testConnection(this->_connection);
}

/*
*  @brief	Method for establish connection.
*           set the connection for network
*  @param	int , struct sockaddr_in
*  @return	int
*/
int	Socket::connectToNetwork(int sock, struct sockaddr_in addr)
{
	//in progress...
}

/*
*  @brief	test _sock or _connection.
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
	return (this->_connection);
}

/*
*  @brief	getter for private attribut address.
*           return the structur address associate
*  @param	void
*  @return	struct sockaddr_in
*/
struct sockaddr_in	Socket::getAddress() const
{
	return (this->_address);
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
