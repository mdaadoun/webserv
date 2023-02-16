/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:31:33 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/16 09:53:26 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASERVER_HPP
# define ASERVER_HPP

//includes
#include <unistd.h> //for read/write (to delete after other implementation)
#include <exception>
#include "../sockets/ListenSocket.class.hpp"

//typedef
typedef unsigned long	u_long;

class Server
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		Server(int dom, int serv, int protoc, int port, u_long interf, int bcklg);
			// destructor //
		~Server();
		//---- getter methods ----//
		ListenSocket	*getSocket() const;
		std::string		getResponse() const;
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
		std::string		_buffer;
		int				_new_socket;
		std::string		_request;
		std::string		_response;

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
