/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:45:44 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/07 10:32:45 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/manager/Manager.class.hpp"

/*
*	@brief	Default constructor of the class Manager.
*			Initialisation for default configuration
*	@param	void
*	@return	void
*/
Manager::Manager():	_read_fds(), _write_fds(),
					_tmp_read_fds(), _tmp_write_fds(),
					_config("conf/config_default.ini")
{
	// init list of fds
	FD_ZERO(&this->_read_fds);
	FD_ZERO(&this->_write_fds);
	FD_ZERO(&this->_tmp_read_fds);
	FD_ZERO(&this->_tmp_write_fds);
}

/*
*	@brief	copy constructor of the class Manager.
*			copy rhs Manager in this Manager
*	@param	Manager &
*	@return	void
*/
Manager::Manager(Manager const &rhs)
{
	*this = rhs;
}

/*
*	@brief	Assignment operator.
*			do nothing
*	@param	Manager &
*	@return	Manager &
*/
Manager	&Manager::operator=(Manager const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*	@brief	Overload constructor of the class Manager.
*			Initialisation with configuration class
*	@param	Config &
*	@return	void
*/
Manager::Manager(Parsing const &conf):	_read_fds(), _write_fds(),
										_tmp_read_fds(), _tmp_write_fds(),
										_config(conf)
{
	// init list of fds
	FD_ZERO(&this->_read_fds);
	FD_ZERO(&this->_write_fds);
	FD_ZERO(&this->_tmp_read_fds);
	FD_ZERO(&this->_tmp_write_fds);
}

/*
*	@brief	getter for _read_fds.
*			return a ptr of list read fd
*	@param	void
*	@return	fd_set
*/
fd_set  *Manager::getListReadFd() const
{
	return ((fd_set *)&this->_read_fds);
}

/*
*	@brief	getter for _tmp_read_fds.
*			return a ptr of list read fd
*	@param	void
*	@return	fd_set
*/
fd_set  *Manager::getListTmpReadFd() const
{
	return ((fd_set *)&this->_tmp_read_fds);
}

/*
*	@brief	getter for _write_fds.
*			return a ptr of list read fd
*	@param	void
*	@return	fd_set
*/
fd_set  *Manager::getListWriteFd() const
{
	return ((fd_set *)&this->_write_fds);
}

/*
*	@brief	getter for _tmp_write_fds.
*			return a ptr of list read fd
*	@param	void
*	@return	fd_set
*/
fd_set  *Manager::getListTmpWriteFd() const
{
	return ((fd_set *)&this->_tmp_write_fds);
}

/*
*	@brief	getter for _connections.
*			return a ptr of map of connections 
*	@param	void
*	@return	std:map<int, int> *
*/
std::map<int, int>  *Manager::getMapConnect() const
{
	return ((std::map<int, int> *)&this->_connections);
}


// variable globale pour exit avec ctrl+c
Manager	*g_this;
/*
*	@brief	Initialisation all connections.
*			Initialisation of all servers
*	@param	void
*	@return	void
*/
void	Manager::initConnections()
{
	// add stdin in tmp_fds for ctrl+c gestion
	FD_SET(0, &this->_tmp_read_fds);
	// create vector of servers function to the config file
	int	nb_serv = this->_config.getServers().size();
	for (int i = 0; i < nb_serv; i++)
	{
		Server	*s = new Server(this->_config, i);
		this->_servers.push_back(s);
	}
	// init fds for connection for all server
	std::vector<Server *>::iterator	it = this->_servers.begin();
	std::vector<Server *>::iterator	ite = this->_servers.end();
	for (; it != ite; it++)
	{
		(*it)->launch();
		FD_SET((*it)->getSocketFd(), &this->_tmp_read_fds);
		this->_connections[(*it)->getSocketFd()] = (*it)->getSocketFd();
	}
	g_this = this;
	//for debug
	signal(SIGINT, SIG_IGN);
}

/*
*	@brief	stop the conmnections.
*			close and delete properly datas before exit program
*	@param	void
*	@return	void
*/
void	Manager::stopProgram()
{
	this->_connections.clear();
	throw (Manager::EndOfWebserv());
}

/*
*	@brief	Management all program.
*			manage all connections/servers for process
*	@param	void
*	@return	void
*/
void	Manager::managementProcess()
{
	while (true)
	{
		std::cout << "*============ WAITING REQUEST ============*" << std::endl;
		// cpy fds tmp in list for working
		this->_read_fds = this->_tmp_read_fds;
		this->_write_fds = this->_tmp_write_fds;
		// allows the program to monitor multiple fds
		std::map<int, int>::iterator	it_max;
		it_max = std::max_element(this->_connections.begin(), this->_connections.end());
		int max_fd = (*it_max).second + 1;
		if (select(max_fd, &this->_read_fds, &this->_write_fds, NULL, NULL) == -1)
			throw(std::runtime_error(strerror(errno)));
		// exit possibilities of webserv
		if (FD_ISSET(0, &this->_read_fds))
			this->serverMenu();
		// check_and_work for all server
		std::vector<Server *>::iterator	it = this->_servers.begin();
		std::vector<Server *>::iterator	ite = this->_servers.end();
		for (; it != ite; it++)
		{
			Server	*serv = *it;
			// create  new communication socket in the server if hes fd is set
			if (FD_ISSET(serv->getSocketFd(), &this->_read_fds))
			{
				std::cout << "@@@@@@@@  create comSocket @@@@@@@@\n";
				int	com_fd = serv->createNewCom();
				// set fd in array of connections
				this->_connections[com_fd] = com_fd;
				FD_SET(com_fd, &this->_tmp_read_fds);
			}
			serv->comManagement(*this);
		}
	}
}

/*
*	@brief	Manage the webserv.
*			Handle exit or restart webserv
*	@param	void
*	@return	void
*/
void	Manager::serverMenu()
{
	std::string input;
	std::getline(std::cin, input);
	if (input.empty() || input == "exit")
	{
		std::cout << "webserver is being closed..." << std::endl;
		stopProgram();
	}
	else if (input == "help")
	{
		std::cout	<< "Please use one of these commands:" << std::endl
					<< std::endl
					<< "\thelp\t\tFor this help" << std::endl
					<< "\texit\t\tShut down the server" << std::endl;
	}
	else
	{
		std::cout << "Command not found.\n\tType [help] for available commands" << std::endl;
	}
}

/*
*	@brief	Class member for exit webserv.
*			close webserv properly
*	@param	void
*	@return	void
*/
char const	*Manager::EndOfWebserv::what() const throw()
{
	return ("Webserv properly closed...!");
}

/*
*	@brief	Destructor of the class Manager.
*			Destroy the Manager object
*	@param	void
*	@return	void
*/
Manager::~Manager()
{
	//voir pour destruction des server.
    std::vector<Server *>::iterator	it = this->_servers.begin();
    std::vector<Server *>::iterator	ite = this->_servers.end();
    for (; it != ite; it++)
    {
        delete (*it);
    }
    this->_servers.clear();
}
