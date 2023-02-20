/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 07:55:47 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

//includes files tests .cpp
#include "test/socket.test.cpp" // propose to move it as a main and compile it with make test_socket

int main()
{
	{// test Sockest
	std::cout << "***** WebServ *****" << std::endl;
	std::cout << "   starting test" << std::endl;
	std::cout << "*******************\n\n";
	socketTest();
	std::cout << "*******************\n\n";
	}//end of test Sockets

	Server	serv(10);
	serv.launch();
    return 0;
}
