/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 11:43:40 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

int main(int ac, char **av)
{
	if (ac < 3)
	{
		switch (ac)
		{
			case 0: { return (1); break; }
			case 1:
			{	
				try
				{
					Config config("conf/config_default.ini");
					// construction du Manager
					// lancement du manager
					Server	serv(config, 1);
					serv.launch();
				}
				catch (std::execption &e)
					std::cout << e.what() << std::endl;
				break;
			}
			case 2:
			{
				try
				{
					Config config(av[1]);
					Server serv(config, 1);
					serv.launch();
				}
				catch (std::exeption &e)
					std::cout << e.what() << std::endl;
				break;
			}
			default : return (1); break;
		}
	}
	else
		std::cout << "Usage: ./webserv [configuration file]" << std::endl;
    return 0;
}
