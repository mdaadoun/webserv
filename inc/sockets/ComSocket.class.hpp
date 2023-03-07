/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComSocket.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/06 16:03:00 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef COMSOCKET_HPP
# define COMSOCKET_HPP

// includes
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <string>
#include <exception>
#include <sys/types.h>
#include <sys/socket.h>
#include "response/Response.class.hpp"
#include "request/Request.class.hpp"
#include "../parsing/Parsing.hpp"

class ComSocket
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		ComSocket(int fd, Parsing const &config);
			// destructor //
		~ComSocket();
		//---- getters methods ----//
		std::string	getIPP() const;
		int			getFdSocket() const;
		bool		getIsOpen() const;

		//---- setter methods ----//
		void	setIsOpen(bool open);

		//---- member methods ----//
		bool	isReceived();
		void	parseRequest(int const nb_serv);
		void	setResponse();
		void	sendResponse();
		void	clear();

	private:
		//---- member object ----//
		struct sockaddr_in	_addr;
		int					_fd_com;
		int					_nb_server;
		bool				_is_open;
		bool				_is_send;
		std::string			_received;
		Response			_response;
		Request				_request;
		Parsing				_config;

		//---- private methods ----//
			// canonical form
		ComSocket();
		ComSocket(ComSocket const &rhs);
		ComSocket	&operator=(ComSocket const &rhs);
			// error test
		void	testConnection(int data, std::string const &err);

};

#endif
