#include "../../inc/main.hpp"

void    Parsing_Test(std::string file)
{
    try
    {
        Parsing parser(file);
        parser.printMap();
        std::cout << "Print port Parser" << std::endl;
        std::cout << parser.getPort() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}