/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:31:33 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/28 15:35:49 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

//includes
#include <unistd.h>
#include <fcntl.h>
#include <exception>
#include <vector>
#include <string>
#include <cstdlib>
#include "../sockets/ListenSocket.class.hpp"
#include "../sockets/ComSocket.class.hpp"
#include "../parsing/Config.hpp"
#include "../parsing/Parsing.hpp"
#include "../request/Request.class.hpp"
#include "../response/Response.class.hpp"
#include "../manager/Manager.class.hpp"

//typedef
typedef unsigned long	u_long;

class Manager;

class Server
{
	public:
		//---- canonical form ----//
			// constructors //
				// copy constructor
		Server(Server const &rhs);
				// overload constructor
		Server(Parsing &config, int n_serv);
			// assignment operator //
		Server	&operator=(Server const &rhs);
			// destructor //
		~Server();
		
		//---- getter methods ----//
		ListenSocket	*getSocket() const;
		int				getSocketFd() const;
		
		//---- member methods ----//
		void	launch();
		int		createNewCom();
		void	comManagement(Manager &manager);
		
		//---- exception class ----//
		class ErrorAccept : public std::exception
		{
			public:
				char const	*what() const throw();
		};
	private:
		//---- member objects ----//
		ListenSocket				*_socket;
		std::vector<ComSocket *>	_all_com;

		//dans la map du parsing
		int															_port;
		std::string													_host;
		std::string													_auto_index;
		std::string													_index;
		std::string													_root;
		std::string													_server_name;
		u_long														_max_size;
		std::map<std::string, std::map<std::string, std::string> >	_locations;
		// autre
		std::string													_error_file;
		int															_new_socket;

		//---- canonical form ----//
				// default constructor
		Server();
};

#endif
