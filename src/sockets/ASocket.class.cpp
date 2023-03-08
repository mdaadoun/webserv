/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:06:39 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/08 11:15:41 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/ASocket.class.hpp"

/*
*  @brief	Default constructor of the class ASocket.
*           Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
ASocket::ASocket()
{
}

/*
*  @brief	Overload constructor of the class ASocket.
*           Initialize the socket with parameters
*  @param	int , int , int , int , unsigned long
*  @return	void
*/
ASocket::ASocket(int dom, int serv, int protoc, int port, std::string &host)
{
	//set values in address struct for connection
	this->_addr.sin_family = dom;
		//set octets in order for nertwork (htons, htonl)
	this->_addr.sin_port = htons(port);
	// set host address
	if (host != "0.0.0.0" || host != "localhost")
		this->_addr.sin_addr.s_addr = inet_addr(host.c_str());
	else
		this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//establish the socket and test
	this->_sock_fd = socket(dom, serv, protoc);
	testConnection(this->_sock_fd, std::string("Error: fd socket."));
	int x = 1;
	int opt = setsockopt(this->_sock_fd, SOL_SOCKET, SO_REUSEPORT, &x, sizeof(x));
	testConnection(opt, std::string("Error: set option socket."));
}

/*
*  @brief	Copy  constructor.
*           Initialize the socket with other socket
*  @param	ASocket &
*  @return	void
*/
ASocket::ASocket(const ASocket& rhs)
{
	*this = rhs;
}

/*
*  @brief	Assignment operator.
*           Copy other socket in this socket
*  @param	ASocket &
*  @return	ASocket &
*/
ASocket  &ASocket::operator=(const ASocket& rhs)
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
void	ASocket::testConnection(int data, std::string const &err)
{
	if (data < 0)
	{
		std::cout << err << std::endl;
		throw std::runtime_error(strerror(errno));
	}
}

/*
*  @brief	Getter for private attribut socket.
*           Return the socket associate
*  @param	void
*  @return	int
*/
int	ASocket::getSocketFd() const
{
	return (this->_sock_fd);
}

/*
*  @brief	Getter for private attribut connection.
*           Return the connection associate
*  @param	void
*  @return	int
*/
int	ASocket::getConnection() const
{
	return (this->_connec);
}

/*
*  @brief	Getter for private attribut address.
*           Return the structur address associate
*  @param	void
*  @return	struct sockaddr_in
*/
struct sockaddr_in	ASocket::getAddress() const
{
	return (this->_addr);
}

/*
*  @brief	Destructor
*           Destroy all member objects
*  @param	void
*  @return	void
*/
ASocket::~ASocket()
{
}
