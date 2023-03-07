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

class RequestHandler {
public:
    // constructor/destructor
    RequestHandler(Request const & req, Config * conf);
    ~RequestHandler(void);

    // setters
    void setStatusCode(int code);
    void setContentType(std::string path);

    // response getters
    std::string getStatusCodeString();
    std::string getProtocolVersion() const;
    std::string getContentType() const;
    std::string getBody() const;
    std::string getDate();

    // main
    void run(void);

    // utils
    void initStatusCodeBook();
    int getStatusCode();
    std::string getErrorPagePath();

    std::map<std::string, std::string> &getRequest(void);


    // Readings
    bool checkLastModified(std::string & path);
    std::string readContent(std::string & path);

    // Methods
    void getMethod();
    void headMethod();
    void postMethod();
    void connectMethod();
    void deleteMethod();
    void putMethod();
    void optionsMethod();
    void traceMethod();

    m_METHOD resolveMethod(std::string & method);

private:
    std::map<std::string, std::string> _request;
//    std::map<std::string, std::string> _response;

    // CONFIG data
    std::string													_auto_index;
    std::string													_index_file;
    std::string													_files_root;
    std::string													_server_name;
    u_long														_client_body_size_limit;
    std::string                                                 _400_file;
    std::string                                                 _401_file;
    std::string                                                 _403_file;
    std::string                                                 _404_file;
    std::string                                                 _405_file;
    std::string                                                 _410_file;
    std::string                                                 _413_file;
    std::string                                                 _500_file;
    std::string                                                 _503_file;
    std::map<std::string, std::map<std::string, std::string> >	_locations;
    std::map<std::string, std::map<std::string, std::string> >	_cgi_list;

    // REQUEST/RESPONSE data
    std::map<int, std::string>                                  _status_code_registry;
    int                                                         _status_code;
    std::string                                                 _request_method;
    std::string                                                 _protocol_version;
    std::string                                                 _content_type;
    std::string                                                 _body;
};

std::ostream &operator<<(std::ostream &out, RequestHandler &rh);

#endif