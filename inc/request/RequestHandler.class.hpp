
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
//# include "server/Server.class.hpp"
# include "request/Request.class.hpp"

class RequestHandler {
public:
    RequestHandler(Request const & req);
//    RequestHandler(Server &serv, Request &req);
    ~RequestHandler(void);


    // setters
    void setStatusCode(int code);
    void setContentType(std::string path);

    // responsee getters
    std::string getStatusCodeString();
    std::string getProtocolVersion() const;
    std::string getContentType() const;
    std::string getBody() const;
    std::string getDate();

    // utils
    void initStatusCodeBook();
    int getStatusCode();
    std::string getErrorPagePath();

    std::map<std::string, std::string> &getRequest(void);

    void run(void);

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
    std::map<std::string, std::string> _response;

    std::map<int, std::string> _status_code_registry;
    int _status_code;
    std::string _protocol_version;

    std::string _files_root;
    std::string _index_file;
    std::string _400_file;
    std::string _401_file;
    std::string _403_file;
    std::string _404_file;
    std::string _405_file;
    std::string _410_file;
    std::string _413_file;
    std::string _500_file;
    std::string _503_file;

    std::string _content_type;
    std::string _body;
};

std::ostream &operator<<(std::ostream &out, RequestHandler &rh);

#endif