/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/14 17:33:38 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

//includes files tests .cpp
#include "test/socket.test.cpp" // propose to move it as a main and compile it with make test_socket
#include "test/parsing.test.cpp"

int main()
{
	{// test Sockest
	std::cout << "***** WebServ *****" << std::endl;
	std::cout << "   starting test" << std::endl;
	std::cout << "*******************\n\n";
	socketTest();
	std::cout << "*******************\n\n";
	}//end of test Sockets

    Parsing_Test("config_default.ini");
	Server	serv(AF_INET, SOCK_STREAM, 0, 2424, INADDR_ANY, 10);
	serv.launch();
    return 0;
}
