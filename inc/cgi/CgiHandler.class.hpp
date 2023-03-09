#pragma once
#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

# include <iostream>
# include <map>
//#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
//# include "../request/Request.class.hpp"
//# include "../parsing/Config.hpp"
//# include "../location/Location.class.hpp"
# include "request/RequestHandler.class.hpp"

class RequestHandler;

class CgiHandler {
public:
    CgiHandler(RequestHandler const &rh);
    CgiHandler(CgiHandler const &src);
    ~CgiHandler(void);

    CgiHandler	&operator=(CgiHandler const &src);

    void                                set_env(void);
    std::map<std::string, std::string> &get_env(void);
    char **                             get_env_char();

    // execute script and return body
    std::string		executeCgi();

private:
//    RequestHandler const &              _request;
    std::string                         _script;
    std::string                         _cgi_interpreter;
    std::map<std::string, std::string>	_env;
    char **                              _env_char;
    std::string							_body; // cgi output

};

std::ostream &operator<<(std::ostream &out, CgiHandler &ch);

#endif