#pragma once
#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

# include <iostream>
# include <map>
//# include "../request/Request.class.hpp"
//# include "../parsing/Config.hpp"
//# include "../location/Location.class.hpp"

class CgiHandler {
public:
    CgiHandler(void);
//    CgiHandler(Request &request, Config &config, Location &location);
    CgiHandler(CgiHandler const &src);
    ~CgiHandler(void);

    CgiHandler	&operator=(CgiHandler const &src);

    void                                set_env(void);
    std::map<std::string, std::string> &get_env(void);

    // execute script and return body
    std::string		executeCgi();


private:
//    Config                              _conf;
//    Request                             _request;
//    Location                            _loc;
    std::string                         _script;
    std::map<std::string, std::string>	_env;

//    std::string							_body; // cgi output

};


std::ostream &operator<<(std::ostream &out, CgiHandler &ch);

#endif