#pragma once
#ifndef HANDLE_REQUEST_HPP
#define HANDLE_REQUEST_HPP

# include "../enum.hpp"
# include <iostream>
# include <map>
# include <sys/stat.h>
# include <ctime>
# include <cstring>
# include <sstream>
# include "parsing/Config.hpp"
# include "parsing/Parsing.hpp"
# include "request/Request.class.hpp"
# include "cgi/CgiHandler.class.hpp"

class RequestHandler {
public:
    // constructor/destructor
    RequestHandler(Request const & req, Config * conf);
    ~RequestHandler(void);

    // setters
    void setStatusCode(int code);
    void setContentType(std::string path);

    // response getters
    int         getStatusCode();
    std::string getStatusCodeString();
    std::string getProtocolVersion() const;
    std::string getContentType() const;
    std::string getBody() const;
    std::string getDate();
    std::string getMethod() const;
    std::string getRoot() const;
    std::string getRequestLocation() const;
    std::string getRequestFile() const;
    std::string getRequestURI() const;
    std::string getCgiInterpreter() const;
    std::map<std::string, std::string> getQueryString() const;

    // main
    void run(void);

    // utils
    bool        checkIfMethodIsAllowed();
    std::string getErrorPagePath();

    std::map<std::string, std::string> &getRequest(void);


    // Readings
    bool checkLastModified(std::string & path);
    std::string readContent(std::string & path);

    // CGI
    bool checkIfCGI(void);
    void runCGI(void);

    // Methods
    void runGETMethod();
    void runHEADMethod();
    void runPOSTMethod();
    void runDELETEMethod();

    m_METHOD resolveMethod(std::string & method);

private:
    // CONFIG data
    std::string													_auto_index;
    std::string													_index_file;
    std::string													_files_root;
    std::string													_server_name;
    u_long														_client_body_size_limit;
    std::map<std::string, std::string>                          _errorPages;
    std::map<std::string, std::string>                         _query_string;
    std::map<std::basic_string<char>, std::map<std::basic_string<char>, std::basic_string<char> > > _locations;
    std::map<std::basic_string<char>, std::map<std::basic_string<char>, std::basic_string<char> > >	_cgi_list;

    // REQUEST/RESPONSE data
    std::string                                                 _request_IfModifiedSince;
    std::map<int, std::string>                                  _status_code_registry;
    int                                                         _status_code;
    std::string                                                 _request_method;
    std::string                                                 _request_location;
    std::string                                                 _request_file;
    std::string                                                 _protocol_version;
    std::string                                                 _content_type;
    std::string                                                 _body;

    std::string                                                 _cgi_interpreter;
};

std::ostream &operator<<(std::ostream &out, RequestHandler &rh);

#endif