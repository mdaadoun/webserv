/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:29:43 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/06 16:23:16 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.class.hpp"

/*
*  @brief	Default constructor of the class Server.
*           Initialize the server without any parameters
*  @param	void
*  @return	void
*/
Server::Server():	_port(2424),
					_host("0.0.0.0"),
					_server_name("webserv"),
					_config(Parsing("conf/config_default.ini"))
{
}

/*
*  @brief	Overload constructor of the class ISocket.
*           Initialize the server with parameters
*  @param	int
*  @return	void
*/
Server::Server(Parsing &config, int n_serv)
{
	this->_port = atoi(config.getNServer(n_serv)->getPort().c_str());
	this->_nb_server = n_serv;
	this->_host = config.getNServer(n_serv)->getIp();
	this->_config = config;
	this->_server_name = config.getNServer(n_serv)->getServerName();
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
	this->_port = rhs._port;
	this->_host = rhs._host;
	this->_server_name = rhs._server_name;
	this->_config = rhs._config;
	this->_new_socket = rhs._new_socket;
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
*  @brief	Getter file descriptor socket.
*           Access to the fd of the socket 
*  @param	void
*  @return	int
*/
int	Server::getSocketFd() const
{
	return (this->_socket->getSocketFd());
}

/*
*  @brief	methode launch.
*           launch the methods accepter, handler and responder for communication 
*  @param	void
*  @return	void
*/
void	Server::launch()
{
	this->_socket = new ListenSocket(PF_INET, SOCK_STREAM, 0, this->_port, this->_host, 10);
	// set non_bolcking the socket
	int setting = fcntl(this->_socket->getSocketFd(), F_SETFL, O_NONBLOCK);
	if (setting == -1)
	{
		std::cerr << "Error: set non-blocking ListenSocket: " << this->_server_name << std::endl;
		throw std::runtime_error(strerror(errno));
	}
}

/*
*  @brief	Create a ComSocket object.
*           create ComSocket form server socket fd and add in array of communications
*  @param	int
*  @return	int
*/
int	Server::createNewCom()
{
	ComSocket	*newCom = new ComSocket(this->_socket->getSocketFd(), this->_config);
	this->_all_com.push_back(newCom);
	return (newCom->getFdSocket());
}

/*
*  @brief	Management communication.
*           Manage the communications for the server
*  @param	void
*  @return	void
*/
void	Server::comManagement(Manager &manager)
{
	std::vector<ComSocket *>::iterator	it = this->_all_com.begin();
	std::vector<ComSocket *>::iterator	ite = this->_all_com.end();
	while (it != ite)
	{
		ComSocket	*com = *it;
		// check fd comSocket is in fds read list
		if (FD_ISSET(com->getFdSocket(), manager.getListReadFd()))
		{
			std::cout << "@@@@@@@@ Request in reception @@@@@@@@\n";
			if (com->isReceived() == true)
			{
				std::cout << "@@@@@@@@ Request is received @@@@@@@@\n";
				FD_SET(com->getFdSocket(), manager.getListTmpWriteFd());
			}
		}
		// check if fd comSocket is in fds write list
		if (FD_ISSET(com->getFdSocket(), manager.getListWriteFd()))
		{
			// parsing string request received
			std::cout << "@@@@@@@@ Parsing request @@@@@@@@\n";
			com->parseRequest(this->_nb_server);
			try
			{
				//set the response in a string
				std::cout << "@@@@@@@@ Setting response @@@@@@@@\n";
				com->setResponse();
				// send the response
				std::cout << "@@@@@@@@ Send response @@@@@@@@\n";
				com->sendResponse();
				// reset the request and response for reuse
				com->clear();
			}
			catch (std::exception &e)
			{
				com->setIsOpen(false);
				std::cerr << "Error: response not properly established !" << std::endl;
				std::cerr << e.what() << std::endl;
			}
			// supp the fds on list tmp write fds
			FD_CLR(com->getFdSocket(), manager.getListTmpWriteFd());
		}
		// check if com socket fd is closed
		if (!com->getIsOpen())
		{
			// supp the fd on tmp read and write list fds and in array of all connections
			FD_CLR(com->getFdSocket(), manager.getListTmpWriteFd());
			FD_CLR(com->getFdSocket(), manager.getListTmpReadFd());
			manager.getMapConnect()->erase(com->getFdSocket());
			// supp communication of array of comm
			delete *it;
			this->_all_com.erase(it);
			// check for stop this communication
			if (this->_all_com.empty())
				break;
			else
			{
				// return at the begin of array of communications
				it = this->_all_com.begin();
				continue;
			}
		}
		it++;
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
