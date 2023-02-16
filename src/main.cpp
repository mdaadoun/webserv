/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/16 10:06:26 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

//includes files tests .cpp
#include "test/socketTest.cpp"

int main()
{
	{// test Sockest
	std::cout << "***** WebServ *****" << std::endl;
	std::cout << "   starting test" << std::endl;
	std::cout << "*******************\n\n";
	socketTest();
	std::cout << "*******************\n\n";
	}//end of test Sockets


	Server	serv(AF_INET, SOCK_STREAM, 0, 2424, INADDR_ANY, 10);
	serv.launch();
    return 0;
}
