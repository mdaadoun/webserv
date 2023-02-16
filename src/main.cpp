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

void    Socket_Test(int port)
{
    std::cout << "***** WebServ *****" << std::endl;
    std::cout << "   starting test" << std::endl;
    std::cout << "*******************\n\n";
    std::cout << "---BindSocket--- :" << std::endl;
    try
    {
        BindSocket	bsock(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY);

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
        ListenSocket	lsock(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10);

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
        ClientSocket	csock(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY);

        std::cout << "getter fd socket = " << csock.getSocket() << std::endl;
        std::cout << "getter connection socket = " << csock.getConnection() << std::endl;
        std::cout << "getter address socket = " << csock.getAddress().sin_addr.s_addr << std::endl;
        std::cout << "\nSocket connection passed...\n\n";
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error::./webserv <FILE>" << std::endl;
        return (-1);
    }
    Parsing_Test(av[1]);
    return 0;
}
