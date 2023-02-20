/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:45:00 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 16:37:27 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <map>
#include <vector>
//#include <exception>
//#include <string>
//#include <cstdlib>	
#include "../server/Server.class.hpp"
#include "../parsing/Config.class.hpp"

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
		
		//---- member methods ----//
		void	initConnections();

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
		void	signalQuit(int val);
			// exit the program //
		void	stopProgram();
			// manage alls connections //
		void	managementProcess();
};

#endif
