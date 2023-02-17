/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:47:09 by fleblanc          #+#    #+#             */
/*   Updated: 2023/02/17 10:41:10 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

int main(void)
{
	std::string	input;

	std::cout << "Select your tests :" << std::endl;
	std::cout << "1 - Socket tests" << std::endl;
	std::cout << "2 - Parsing tests" << std::endl;
	std::cout << "3 - Response tests" << std::endl;
	std::cout << "9 - All tests" << std::endl;

	std::cout << "Command : ";
	std::getline(std::cin, input);
	if (std::cin.eof())
	{
		std::cout << std::endl;
		return (0);
	}
	switch (atoi(input.c_str()))
	{
		case 1:
			socketTest();
			break;
		case 2:
			parsingTest();
			break;
		case 3:
			responseTest();
			break;
		case 9:
			socketTest();
			parsingTest();
			responseTest();
			break;
		default:
			std::cout << "Good Bye !" << std::endl;
			break;
	}

	return (0);
}
