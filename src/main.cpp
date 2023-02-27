/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/17 17:53:55 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

//includes files tests .cpp
#include "test/socket.test.cpp" // propose to move it as a main and compile it with make test_socket

int main()
{
//	{// test Sockets
//	std::cout << "***** WebServ *****" << std::endl;
//	std::cout << "   starting test" << std::endl;
//	std::cout << "*******************\n\n";
//	socketTest();
//	std::cout << "*******************\n\n";
//	}//end of test Sockets
//		std::cout << "getter fd socket = " << csock.getSocket() << std::endl;
//		std::cout << "getter connection socket = " << csock.getConnection() << std::endl;
//		std::cout << "getter address socket = " << csock.getAddress().sin_addr.s_addr << std::endl;
//		std::cout << "\nSocket connection passed...\n\n";
//	}
//	catch (std::exception &e) {
//        std::cout << e.what() << std::endl;
//    }
//	std::map<std::string, std::string>	config;
//    parse_config_file(&config, "config.ini");
	Server	serv(10);
	serv.launch();
    return 0;
}
