/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:45:00 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/24 14:02:11 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <signal.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <algorithm>
#include <exception>
#include <string>
#include "server/Server.class.hpp"
#include "parsing/Config.class.hpp"

class Server;

class Manager
{
	public:
		//---- canonical form ----//
			// constructors //
				// default constructor
		Manager();
				// overload constructor
		Manager(Config const &conf);
			// destructor //
		~Manager();
		
		//---- getter methods ----//
		fd_set				*getListReadFd() const;
		fd_set				*getListTmpReadFd() const;
		fd_set				*getListWriteFd() const;
		fd_set				*getListTmpWriteFd() const;
		std::map<int, int>	*getMapConnect() const;

		//---- member methods ----//
		void	initConnections();
			// manage alls connections
		void	managementProcess();

	private:
		//---- member objects ----//
			// list of fds for select() and tmp for save datas
		fd_set					_read_fds,
								_write_fds,
								_tmp_read_fds,
								_tmp_write_fds;
			// stock all fd connected from servers
		std::map<int, int>		_connections;
			// array of servers
		std::vector<Server *>	_servers;
			// config for all servers
		Config					_config;

		//---- private member methods ----//
				// copy constructor
		Manager(Manager const &rhs);
			// assignment operator //
		Manager	&operator=(Manager const & rhs);
			// handler signal ctrlC //
		static void	signalQuit(int val);
			// exit the program //
		void	stopProgram();
};

#endif