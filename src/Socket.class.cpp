/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:06:39 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/10 12:20:30 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.class.hpp"

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
ISocket::ISocket() {};

/*
*  @brief	Default constructor of the class ISocket.
*           Initialize the socket with parameters
*  @param	int , int , int , int , unsigned long
*  @return	void
*/
ISocket::ISocket(int dom, int serv, int protoc, int port, uint32_t interf)
{
	//set values in address struct for connection
	_address.sin_family = dom;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(interf);
	//establish ths ssocket
	_socket = socket(dom, serv, protoc);
}
