/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:53:06 by dlaidet           #+#    #+#             */
/*   Updated: 2023/02/17 17:53:30 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

static void  Def_Parsing()
{
    try
    {
        std::cout << "===Default Constructor and print content of map===" << std::endl;
        Config parser;
        std::vector<std::map<std::string, std::string> > list = parser.getList();
        std::vector<std::map<std::string, std::string> >::iterator it;
        std::cout << "Vector Size" << std::endl;
        std::cout << list.size() << std::endl;
        it = list.begin();
        while (it != list.end())
        {
            parser.printMap(it);
            it++;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

static void  Over_Parsing()
{
    try
    {
        std::cout << "===Overload Constructor and print content of map===" << std::endl;
        Config parser("conf/config_test_over.ini");
        std::vector<std::map<std::string, std::string> > list = parser.getList();
        std::vector<std::map<std::string, std::string> >::iterator it;
        std::cout << "Vector Size" << std::endl;
        std::cout << list.size() << std::endl;
        it = list.begin();
        while (it != list.end())
        {
            parser.printMap(it);
            it++;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

static void  Copy_Parsing()
{
    try
    {
        std::cout << "===Copy Constructor and print content of map===" << std::endl;
        Config parser("conf/config_test_copy.ini");
        std::vector<std::map<std::string, std::string> > list = parser.getList();
        std::vector<std::map<std::string, std::string> >::iterator it;
        it = list.begin();
        while (it != list.end())
        {
            parser.printMap(it);
            it++;
        }
        std::cout << "===Making Copy===" << std::endl;
        Config copy(parser);
        std::vector<std::map<std::string, std::string> > clist = copy.getList();
        std::vector<std::map<std::string, std::string> >::iterator cit;
        cit = clist.begin();
        while (cit != clist.end())
        {
            parser.printMap(cit);
            cit++;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void    parsingTest()
{
    std::string	input;

    std::cout << "===Welcome in parsing test===" << std::endl;
    std::cout << "Select your tests :" << std::endl;
    std::cout << "1 - Default Constructor and print content of map" << std::endl;
    std::cout << "2 - Overload Constructor and print content of map" << std::endl;
    std::cout << "3 - Copy Constructor and print content of map" << std::endl;
    std::cout << "9 - All tests" << std::endl;

    std::cout << "Command : ";
    std::getline(std::cin, input);
    if (std::cin.eof())
    {
        std::cout << std::endl;
        return ;
    }
    switch (atoi(input.c_str()))
    {
        case 1:
            Def_Parsing();
            break;
        case 2:
            Over_Parsing();
            break;
        case 3:
            Copy_Parsing();
            break;
        case 9:
            Def_Parsing();
            break;
        default:
            std::cout << "Good Bye !" << std::endl;
            break;
    }
}
