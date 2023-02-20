/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:45:44 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 16:36:22 by tlafont          ###   ########.fr       */
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
Manager::Manager(Config const &conf):	_read_fds(), _write_fds(),
										_tmp_read_fds(), _tmp_write_fds(),
										_config(conf)
{
	// init list of fds
	FD_ZERO(&this->_read_fds);
	FD_ZERO(&this->_write_fds);
	FD_ZERO(&this->_tmp_read_fds);
	FD_ZERO(&this->_tmp_write_fds);
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
	int	nb_serv = this->_config.getList().size();
	for (int i = 0; i < nb_serv; i++)
	{
		Server	*s = new Server(this->_config, i);
		this->_servers.push_back(s);
	}
	// init fds for connection for all server
	std::vector<Server *>::iterator	it = this->_server.begin();
	std::vector<Server *>::iterator	ite = this->_server.end();
	for (; it != ite; it++)
	{
		(*it)->launch();
		FD_SET((*it)->getSocketFd(), &this->_tmp_read_fds);
		this->_connections[(*it)->getSocketFd] = (*it)->getSocketFd;
	}
	g_this = this;
	signal(SIGINT, this->signalQuit);
	this->managementProcess();
}

/*
*	@brief	Signal ctrl + c management.
*			quit properly the prog when ctrl+c is called
*	@param	int
*	@return	void
*/
void	Manager::signalQuit(int val)
{
	g_here->stopProgram();
	exit(val);
}

/*
*	@brief	stop the conmnections.
*			close and delete properly datas before exit program
*	@param	void
*	@return	void
*/
void	stopProgram()
{
	std::vector<Server *>::iterator	it = this->_servers.begin();
	std::vector<Server *>::iterator	ite = this->_servers.end();
	for (; it != ite; it++)
		delete *it;
	this->_servers.clear();
	//set to ZERO fds?
	std::cout << "Webserv properly closed...!" <<  std::endl;
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
}
