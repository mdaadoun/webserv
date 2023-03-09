/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:47:09 by fleblanc          #+#    #+#             */
/*   Updated: 2023/03/09 15:21:08 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

int main(int argc, char **argv)
{
	std::string	input;

	if (argc == 2)
		input = argv[1];
	else
	{
		std::cout << "Select your tests :" << std::endl;
        std::cout << "1 - Parsing tests" << std::endl;
		std::cout << "2 - Socket tests" << std::endl;
        std::cout << "3 - Request tests" << std::endl;
        std::cout << "4 - Handling request tests" << std::endl;
        std::cout << "5 - Response test" << std::endl;
        std::cout << "6 - Server test" << std::endl;
        std::cout << "7 - Cgi tests" << std::endl;
		std::cout << "9 - All tests" << std::endl;
		std::cout << std::endl;
		std::cout << "Command : ";
		std::getline(std::cin, input);
		if (std::cin.eof())
		{
			std::cout << std::endl;
			return (0);
		}
	}
	switch (atoi(input.c_str()))
	{
		case 1:
			parsingTest();
			break;
        case 2:
			socketTest();
            break;
        case 3:
			requestTest();
            break;
        case 4:
            handlerRequestTest();
            break;
        case 5:
			responseTest();
            break;
        case 6:
			serverTest();
            break;
		case 7:
            cgiTest();
			break;
		case 9:
			parsingTest();
			socketTest();
			requestTest();
            handlerRequestTest();
			responseTest();
			serverTest();
            cgiTest();
			break;
		default:
			std::cout << "Good Bye !" << std::endl;
			break;
	}

	return (0);
}
