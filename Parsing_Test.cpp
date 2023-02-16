#include"../inc/main.hpp"

void    Parsing_Test(std::string file)
{
    try
    {
        Parsing parser(file);
        parser.printMap();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}