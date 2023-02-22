/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComSocket.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:59 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/22 09:10:14 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef COMSOCKET_HPP
# define COMSOCKET_HPP

// includes
#include <iostream>
#include <string>
#include <exception>
#include <sys/types.h>
#include <sys/socket.h>


class ComSocket
{
	public:
		//---- canonical form ----//
			// constructors //
				// overload constructor
		ComSocket(int fd, std::string serverName);
			// destructor //
		~ComSocket();
		//---- member methods ----//
		std::string	getIPP() const;
		int			getFdSocket() const;

	private:
		//---- member object ----//
		struct sockaddr_in	_addr;
		int					_fd_com;

		//---- private methods ----//
			// canonical form
		ComSocket();
		ComSocket(ComSocket const &rhs);
		ComSocket	&operator=(ComSocket const &rhs);
			// error test
		void	testConnection(int data, std)

};

#endif
