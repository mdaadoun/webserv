/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComSocket.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/23 10:39:35 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef COMSOCKET_HPP
# define COMSOCKET_HPP

// includes
#include <iostream>
#include <cstring>
#include <string>
#include <exception>
#include <sys/types.h>
#include <sys/socket.h>
#include "response/Response.class.hpp"
#include "request/Request.class.hpp"


class ComSocket
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		ComSocket(int fd, std::string serverName);
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
		void	parseRequest();
		void	setResponse();
		void	sendResponse();

	private:
		//---- member object ----//
		struct sockaddr_in	_addr;
		int					_fd_com;
		bool				_is_open;
		std::string			_received;
		Response			_response;
		Request				_request;

		//---- private methods ----//
			// canonical form
		ComSocket();
		ComSocket(ComSocket const &rhs);
		ComSocket	&operator=(ComSocket const &rhs);
			// error test
		void	testConnection(int data, std)

};

#endif
