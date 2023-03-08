/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/08 11:16:49 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

// includes

#include "ASocket.class.hpp"

class BindSocket : public ASocket
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		BindSocket(int dom, int serv, int protoc, int port, std::string &host);

			// destructor //
		~BindSocket();
		//---- member methods ----//
		int connectToNetwork(int sock, struct sockaddr_in addr) const;

	private:
		BindSocket	&operator=(BindSocket const &rhs);
};

#endif
