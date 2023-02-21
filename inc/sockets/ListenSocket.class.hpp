/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:23:08 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/21 12:33:21 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef LISTENSOCKET_HPP
# define LISTENSOCKET_HPP

// includes
#include "BindSocket.class.hpp"

class ListenSocket : public BindSocket
{
	public:
			// constructors //
				// overload constructor
		ListenSocket(int dom, int serv, int protoc, int port, std::string &host, int bcklog);
			// destructor //
		~ListenSocket();
		//---- getter methods ----//
		int	getBcklog() const;
			// getter for fd listenSocket
		int	getListen() const;
		//---- member methods ----//
		int	startListen();
	private:
		int	_backlog;
		int	_listen;

		ListenSocket	&operator=(ListenSocket const &rhs);
};

#endif
