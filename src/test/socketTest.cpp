/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:03:15 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/16 18:43:12 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/main.hpp"
#include "test.hpp"

void	socketTest()  // propose to become a main for testing
{
	std::cout << "---BindSocket--- :" << std::endl;
	try
	{
		BindSocket	bsock(AF_INET, SOCK_STREAM, 0, 8000, INADDR_ANY);

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
		ListenSocket	lsock(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10);

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

	std::cout << "---ClientSocket--- :" << std::endl;
	try
	{
		ClientSocket	csock(AF_INET, SOCK_STREAM, 0, 8070, INADDR_ANY);

		std::cout << "getter fd socket = " << csock.getSocketFd() << std::endl;
		std::cout << "getter connection socket = " << csock.getConnection() << std::endl;
		std::cout << "getter address socket = " << csock.getAddress().sin_addr.s_addr << std::endl;
		std::cout << "\nSocket connection passed...\n\n";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
