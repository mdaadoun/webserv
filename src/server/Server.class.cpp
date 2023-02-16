/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:29:43 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/16 09:54:33 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Server.class.hpp"

/*
*  @brief	Default constructor of the class Server.
*           Initialize the server without any parameters
*  @param	void
*  @return	void
*/
Server::Server()
{
}

/*
*  @brief	Overload constructor of the class ISocket.
*           Initialize the server with parameters
*  @param	int, int, int, int, unsigned long, int
*  @return	void
*/
Server::Server(int dom, int serv, int protoc, int port, u_long interf, int bcklg)
{
	this->_socket = new ListenSocket(dom, serv, protoc, port, interf, bcklg);

}

/*
*  @brief	copy constructor of the class Server.
*           Initialize the server with another Aserver
*  @param	Server &
*  @return	void
*/
Server::Server(Server const &rhs)
{
	*this = rhs;
}

/*
*  @brief	Assignment operator.
*           Copy server with another server
*  @param	Server &
*  @return	Server &
*/
Server	&Server::operator=(Server const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*  @brief	Getter socket.
*           access to the socket datas
*  @param	void
*  @return	ListenSocket *
*/
ListenSocket	*Server::getSocket() const
{
	return (this->_socket);
}

/*
*  @brief	Getter response.
*           access to the response at send
*  @param	void
*  @return	std::string
*/
std::string	Server::getResponse() const
{
	return (this->_response);
}

/*
*  @brief	method accepter.
*           grabs the connection request and creates a new socket for that connection
*  @param	void
*  @return	void
*/
void    Server::accepter()
{
	struct sockaddr_in	addr = this->getSocket()->getAddress();
	int					addr_len = sizeof(addr);
	this->_new_socket = accept(this->getSocket()->getSocketFd(),
							(struct sockaddr *)&addr, (socklen_t *)&addr_len);
	if (this->_new_socket < 0)
		throw Server::ErrorAccept();
	else
		std::cout << "* new request accepted *" << std::endl;
}

/*
*  @brief	method handler.
*           read the receive messages 
*  @param	void
*  @return	void
*/
void	Server::handler()
{
	// to delete with implementation
	char *tmp = new char[30000];
	for (size_t i = 0; i < 30000; i++)
		tmp[i] = '\0';
	long reading = read(this->_new_socket, tmp, 30000);
	if (reading >= 0)
	{
		this->_request = std::string(tmp);
		std::cout << "** request read... **" << std::endl;
		std::cout << this->_request << std::endl;
	}
	else
		std::cout << " ** No bytes are there to read... **" << std::endl;
	delete[] tmp;
}

/*
*  @brief	method responder.
*           send the response messages 
*  @param	void
*  @return	void
*/
void	Server::responder()
{
	std::string	rep = "---> response from Server...\n\nrequest send to server;\n";
	this->_response = rep + this->_request;
	// to delete with implementation
	write(this->_new_socket, this->_response.c_str(), this->_response.size());
	close(this->_new_socket);
}

/*
*  @brief	methode launch.
*           launch the methods accepter, handler and responder for communication 
*  @param	void
*  @return	void
*/
void	Server::launch()
{
	while (true)
	{
		std::cout << "*==== WAITING REQUEST ====*" << std::endl;
		try
		{
			accepter();
			handler();
			responder();
			std::cout << "*======== !DONE! =========*" << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}

	}
}

/*
*  @brief	Error message for exception.
*           Set the msg in case of exception
*  @param	void
*  @return	void
*/
char const	*Server::ErrorAccept::what() const throw()
{
	return ("Server: error accept new socket...");
}

/*
*  @brief	Destructor.
*           destroy the server and parameters
*  @param	void
*  @return	void
*/
Server::~Server()
{
	delete this->_socket;
}

