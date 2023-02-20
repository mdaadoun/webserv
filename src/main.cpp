/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/20 09:35:29 by tlafont          ###   ########.fr       */
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
				Config config("conf/config_default.ini");
				Server	serv(config, 1);
				serv.launch();
				break;
			}
			case 2:
			{
				Config config(av[1]);
				Server serv(config, 1);
				serv.launch();
				break;
			}
			default : return (1); break;
		}
	}
	else
		std::cout << "Usage: ./webserv [configuration file]" << std::endl;
    return 0;
}
