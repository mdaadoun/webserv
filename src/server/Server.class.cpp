/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:29:43 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/27 08:16:54 by tlafont          ###   ########.fr       */
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
					_auto_index("off"),
					_index(),
					_root("./www/html"),
					_server_name("webserv"),
					_max_size(1000000),
					_locations(),
					_error_file("error.html")
{
}

/*
*  @brief	Overload constructor of the class ISocket.
*           Initialize the server with parameters
*  @param	int
*  @return	void
*/
Server::Server(Config &config, int n_serv): _port(atoi(config.getPort(n_serv).c_str())),
											_host(config.getIP(n_serv)),
											_auto_index("off"),
											_index(config.getIndex(n_serv)),
											_root(config.getRoot(n_serv)),
											_server_name(config.getServerName(n_serv)),
											_max_size(1000000),
											_locations(),
											_error_file("error.html")
{
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
	this->_auto_index = rhs._auto_index;
	this->_index = rhs._index;
	this->_root = rhs._root;
	this->_server_name = rhs._server_name;
	this->_max_size = rhs._max_size;
	this->_locations = rhs._locations;
	this->_error_file = rhs._error_file;
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
	ComSocket	*newCom = new ComSocket(this->_socket->getSocketFd(), this->_server_name);
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
			com->parseRequest();
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
