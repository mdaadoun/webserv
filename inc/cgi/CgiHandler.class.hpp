#pragma once
#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

# include <iostream>
# include <map>
#include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "request/RequestHandler.class.hpp"

class RequestHandler;

class CgiHandler {
public:
    // default constructor and destructor
    CgiHandler(RequestHandler const &rh);
    ~CgiHandler(void);

    // constructor by copy and = overloading
    CgiHandler(CgiHandler const &src);
    CgiHandler	&operator=(CgiHandler const &src);

    // env methods
    void                                set_env(void);
    std::map<std::string, std::string> &get_env(void);
    char **                             get_env_char();

    // execute script and return body
    std::string		executeCgi();

private:
    char **                              _env_char;
    std::map<std::string, std::string>	_env;
    std::string                         _script;
    std::string                         _cgi_interpreter;
    std::string							_body;
    std::string							_method;
    std::string                      	_query_string;
};

std::ostream &operator<<(std::ostream &out, CgiHandler &ch);

#endif