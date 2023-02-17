#include "test.hpp"

void    Parsing_Test(std::string file)
{
    try
    {
        Config parser(file);
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