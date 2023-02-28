/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:03:15 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/28 15:37:17 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	socketTest()  // propose to become a main for testing
{
	std::string	host("0.0.0.0");
	std::cout << "\033[0;34m # Socket test # \033[0;0m" << std::endl;
	std::cout << "---BindSocket--- :" << std::endl;
	try
	{
		BindSocket	bsock(AF_INET, SOCK_STREAM, 0, 8000, host);

		std::cout << "getter fd socket = " << bsock.getSocketFd() << std::endl;
		std::cout << "getter connection socket = " << bsock.getConnection() << std::endl;
		std::cout << "getter address socket = " << bsock.getAddress().sin_addr.s_addr << std::endl;
		std::cout << "\nSocket connection passed...\n\n";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "---ListenSocket--- :" << std::endl;
	try
	{
		ListenSocket	lsock(AF_INET, SOCK_STREAM, 0, 8080, host, 10);

		std::cout << "getter fd socket = " << lsock.getSocketFd() << std::endl;
		std::cout << "getter connection socket = " << lsock.getConnection() << std::endl;
		std::cout << "getter address socket = " << lsock.getAddress().sin_addr.s_addr << std::endl;
		std::cout << "getter backlog socket = " << lsock.getBcklog() << std::endl;
		std::cout << "getter listen socket = " << lsock.getListen() << std::endl;
		std::cout << "\nSocket connection passed...\n\n";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
