/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/15 14:28:13 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

int main()
{
/*	{// test Sockest
	std::cout << "***** WebServ *****" << std::endl;
	std::cout << "   starting test" << std::endl;
	std::cout << "*******************\n\n";
	std::cout << "---BindSocket--- :" << std::endl;
	try
	{
		BindSocket	bsock(AF_INET, SOCK_STREAM, 0, 8000, INADDR_ANY);

		std::cout << "getter fd socket = " << bsock.getSocket() << std::endl;
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

		std::cout << "getter fd socket = " << lsock.getSocket() << std::endl;
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

		std::cout << "getter fd socket = " << csock.getSocket() << std::endl;
		std::cout << "getter connection socket = " << csock.getConnection() << std::endl;
		std::cout << "getter address socket = " << csock.getAddress().sin_addr.s_addr << std::endl;
		std::cout << "\nSocket connection passed...\n\n";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	}//end of test Sockets
*/

	Server	serv(AF_INET, SOCK_STREAM, 0, 2424, INADDR_ANY, 10);
	serv.launch();
    return 0;
}
