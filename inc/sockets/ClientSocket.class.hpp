/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/17 13:49:21 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CLIENTSOCKET_HPP
# define CLIENTSOCKET_HPP

// includes

#include "ISocket.class.hpp"

//Typedef

typedef unsigned long	u_long;

class ClientSocket : public ISocket
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		ClientSocket(int dom, int serv, int protoc, int port, std::string &host);

			// destructor //
		~ClientSocket();
		//---- member methods ----//
		int connectToNetwork(int sock, struct sockaddr_in addr) const;

	private:
		ClientSocket	&operator=(ClientSocket const &rhs);
};

#endif
