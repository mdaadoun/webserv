/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:31:33 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 09:47:25 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASERVER_HPP
# define ASERVER_HPP

//includes
#include <unistd.h> //for read/write (to delete after other implementation)
#include <exception>
#include <vector>
#include <string>
#include <cstdlib>
#include "../sockets/ListenSocket.class.hpp"
#include "../parsing/Config.class.hpp"
#include "../request/Request.class.hpp"
#include "../response/Response.class.hpp"

//typedef
typedef unsigned long	u_long;

class Server
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		Server(Config &config, int n_serv);
			// destructor //
		~Server();
		//---- getter methods ----//
		ListenSocket	*getSocket() const;
//		std::string		getResponse() const;
		//---- member methods ----//
		void	launch();
		//---- exception class ----//
		class ErrorAccept : public std::exception
		{
			public:
				char const	*what() const throw();
		};
	private:
		//---- member objects ----//
		ListenSocket	*_socket;

		//dans la map du parsing
		int							_port;
		std::string					_host;
		std::string					_auto_index;
		std::string					_index;
		std::string					_root;
		std::string					_server_name;
		u_long						_max_size;
		std::vector<std::string>	_locations;
		// autre
		std::string					_buffer;
		std::string					_error_file;
		int							_new_socket;
		Request		    			_request;
		Response	    			_response;

		//---- canonical form ----//
				// default constructor
		Server();
				// copy constructor
		Server(Server const &rhs);
				// assignment operator
		Server	&operator=(Server const &rhs);

		//---- private member methods ----//
		void	accepter();
		void	handler();
		void	responder();
};

#endif
