#include "../../inc/main.hpp"

void    Parsing_Test(std::string file)
{
    try
    {
        Config parser(file);
        std::cout << "Print Map Parser" << std::endl;
        parser.printMap();
        std::cout << "Print IP Parser" << std::endl;
        std::cout << parser.getIP() << std::endl;
        std::cout << "Print port Parser" << std::endl;
        std::cout << parser.getPort() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}