/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:29:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/21 12:34:57 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/ListenSocket.class.hpp"

/*
*	@brief	Overload constructor of the class ListenSocket.
*			Initialize the socket with any parameters
*	@param	int, int, int, int, unsigned long, int
*	@return	void
*/
ListenSocket::ListenSocket(int dom, int serv, int protoc, int port, std::string &host, int bcklog):
BindSocket(dom, serv, protoc, port, host)
{
	this->_backlog = bcklog;
	this->_listen = startListen();
	testConnection(this->_listen, std::string("Error: waiting connection to socket."));
}

/*
*	@brief	Assignment operator.
*			Copy the socket with another ListenSocket
*	@param	ListenSocket &
*	@return	ListenSocket &
*/
ListenSocket	&ListenSocket::operator=(ListenSocket const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*	@brief	Method for establish server listening.
*			Set the listening for server
*	@param	void
*	@return	int
*/
int	ListenSocket::startListen()
{
	return (listen(this->_sock_fd, this->_backlog));
}

/*
*	@brief	Getter for attribut backlog.
*			return the value of backlog
*	@param	void
*	@return	int
*/
int ListenSocket::getBcklog() const
{
	return (this->_backlog);
}

/*
*	@brief	Getter for attribut listen.
*			return the value in listen
*	@param	void
*	@return	int
*/
int	ListenSocket::getListen() const
{
	return (this->_listen);
}

/*
*	@brief	Destructor.
*			destroy the socket
*	@param	void
*	@return	void
*/
ListenSocket::~ListenSocket()
{
}
