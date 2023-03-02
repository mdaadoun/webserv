/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:47:09 by fleblanc          #+#    #+#             */
/*   Updated: 2023/03/01 12:35:54 by tlafont          ###   ########.fr       */
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
		std::cout << "1 - Socket tests" << std::endl;
        std::cout << "2 - Parsing tests" << std::endl;
        std::cout << "3 - Cgi tests" << std::endl;
        std::cout << "4 - parse request tests" << std::endl;
		std::cout << "9 - All tests" << std::endl;

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
			//socketTest();
			break;
        case 2:
            parsingTest();
            break;
        case 3:
            cgiTest();
            break;
        case 4:
            requestTest();
            break;
		case 9:
			//socketTest();
			parsingTest();
            cgiTest();
			requestTest();
			responseTest();
			break;
		default:
			std::cout << "Good Bye !" << std::endl;
			break;
	}

	return (0);
}
