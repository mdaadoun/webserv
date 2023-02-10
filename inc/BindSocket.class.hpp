/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 14:45:42 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

// includes

#include "ISocket.class.hpp"

//Typedef

typedef unsigned long	u_long;

class BindSocket : public ISocket
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		BindSocket(int dom, int serv, int protoc, int port, u_long interf);

			// destructor //
		~BindSocket();
		//---- member methods ----//
		int connectToNetwork(int sock, struct sockaddr_in addr) const;

	private:
		BindSocket();
		BindSocket(BindSocket const &rhs);
		BindSocket	&operator=(BindSocket const &rhs);
};

#endif
