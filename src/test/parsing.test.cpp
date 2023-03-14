/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:53:06 by dlaidet           #+#    #+#             */
/*   Updated: 2023/03/09 14:29:08 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

static void printConfigContent(Config *config)
{
    std::cout << "getIp: " << config->getIp() << std::endl;
    std::cout << "getPort: " << config->getPort() << std::endl;
    std::cout << "getListen: " << config->getListen() << std::endl;
    std::cout << "getRoot: " << config->getRoot() << std::endl;
    std::cout << "getIndex: " << config->getIndex() << std::endl;
    std::cout << "getautoIndex: " << config->getAutoIndex() << std::endl;
    std::cout << "getServerName: " << config->getServerName() << std::endl;
    std::cout << "getClientBodyLimit: " << config->getClientBodyLimit() << std::endl;
    config->printErrorPages();
    config->printLocations();
    config->printCgi();
}

static void  Def_Parsing()
{
    try
    {
        std::cout << "===Default Constructor and print content of Config===" << std::endl;
        Parsing parser;

        std::cout << "Number of servers : ";
        std::cout << parser.getServers().size() << std::endl;
        for (std::string::size_type i = 0; i < parser.getServers().size(); i++)
        {
            std::cout << "========================================================" << std::endl;
            std::cout << "Server name: " << parser.getNServer(i)->getServerName() << std::endl;
            printConfigContent(parser.getNServer(i));
            std::cout << "========================================================" << std::endl;
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
         std::cout << "===Overload Constructor and print content of Config===" << std::endl;
         Parsing parser("conf/config_test_copy.ini");

         std::cout << "Number of servers : ";
         std::cout << parser.getServers().size() << std::endl;
         for (std::string::size_type i = 0; i < parser.getServers().size(); i++)
         {
             std::cout << "========================================================" << std::endl;
             std::cout << "Server name: " << parser.getNServer(i)->getServerName() << std::endl;
             printConfigContent(parser.getNServer(i));
             std::cout << "========================================================" << std::endl;
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
         std::cout << "===Copy Constructor and print content of Config===" << std::endl;
         Parsing parser("conf/config_test_copy.ini");
         Parsing copy(parser);

         std::cout << "Number of servers : ";
         std::cout << copy.getServers().size() << std::endl;
         for (std::string::size_type i = 0; i < copy.getServers().size(); i++)
         {
             std::cout << "========================================================" << std::endl;
             std::cout << "Server name: " << copy.getNServer(i)->getServerName() << std::endl;
             printConfigContent(copy.getNServer(i));
             std::cout << "========================================================" << std::endl;
         }
     }
     catch (std::exception &e)
     {
         std::cout << e.what() << std::endl;
     }
 }

// static void  Getter_Parsing()
// {
//     try
//     {
//         std::cout << "===Default Constructor and use getter===" << std::endl;
//         Config  parser;
//         int     i = 1;
//         std::string errors[9] = {"400", "401", "403", "404", "405", "410", "431", "500", "503"};
//         std::vector<std::map<std::string, std::string> > list = parser.getList();
//         std::vector<std::map<std::string, std::string> >::iterator it;
//         it = list.begin();
//         while (it != list.end())
//         {
//             std::cout << "getMap: " << parser.getMap(i) << std::endl;
//             std::cout << "getIp: " << parser.getIP(i) << std::endl;
//             std::cout << "getListen: " << parser.getListen(i) << std::endl;
//             std::cout << "getPort: " << parser.getPort(i) << std::endl;
//             std::cout << "getRoot: " << parser.getRoot(i) << std::endl;
//             std::cout << "getIndex: " << parser.getIndex(i) << std::endl;
//             std::cout << "getServerName: " << parser.getServerName(i) << std::endl;
//             std::cout << "getClientBodyLimit: " << parser.getClientBodyLimit(i) << std::endl;
//             for (int j = 0; j < 9; j++)
//             {
//                 std::cout << "getErrorPage" << errors[j] << ": " << parser.getErrorPage(i,errors[j]) << std::endl;
//             }
//             std::cout << "getLocAllowMethod: " << parser.getLocAllowMethod(i) << std::endl;
//             std::cout << "getLocContentAllowMethod: " << parser.getLocContentAllowMethod(i) << std::endl;
//             std::cout << "getLocCgiAllowMethod: " << parser.getLocCgiAllowMethod(i) << std::endl;
//             it++;
//             i++;
//         }
//     }
//     catch (std::exception &e)
//     {
//         std::cout << e.what() << std::endl;
//     }
// }

// static void  Spec_Parsing(std::string file)
// {
//     try
//     {
//         std::cout << "===Test Specific config file in directory conf===" << std::endl;
//         Config parser(file);
//         std::vector<std::map<std::string, std::string> > list = parser.getList();
//         std::vector<std::map<std::string, std::string> >::iterator it;
//         std::cout << "Vector Size" << std::endl;
//         std::cout << list.size() << std::endl;
//         it = list.begin();
//         while (it != list.end())
//         {
//             parser.printMap(it);
//             it++;
//         }
//     }
//     catch (std::exception &e)
//     {
//         std::cout << e.what() << std::endl;
//     }
// }

void    parsingTest()
{
     std::string file;
     std::string input;

     std::cout << "\033[0;34m # Welcome in parsing test #\033[0;0m" << std::endl;
     std::cout << "Select your tests :" << std::endl;
     std::cout << "1 - Default Constructor and print content of Config" << std::endl;
     std::cout << "2 - Overload Constructor and print content of Config" << std::endl;
     std::cout << "3 - Copy Constructor and print content of Config" << std::endl;
    // std::cout << "4 - Default Constructor and use getter" << std::endl;
    // std::cout << "8 - Test Specific config file in directory conf" << std::endl;
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
        // case 4:
        //     Getter_Parsing();
        //     break;
        // case 8:
        //     std::cout << "FileName : ";
        //     std::getline(std::cin, file);
        //     file = "conf/" + file;
        //     if (std::cin.eof())
        //     {
        //         std::cout << std::endl;
        //         return ;
        //     }
        //     Spec_Parsing(file);
        //     break;
         case 9:
             Def_Parsing();
             Over_Parsing();
             Copy_Parsing();
        //     Getter_Parsing();
             break;
         default:
             std::cout << "Good Bye !" << std::endl;
             break;
     }
}
