
#pragma once
#ifndef HANDLE_REQUEST_HPP
#define HANDLE_REQUEST_HPP

# include <iostream>
# include <map>
# include <sys/stat.h>
# include "parsing/Config.class.hpp"
# include "server/Server.class.hpp"
# include "request/Request.class.hpp"

typedef enum e_METHOD {
    m_ERROR,
    m_GET,
    m_HEAD,
    m_POST,
    m_DELETE,
    m_PUT,
    m_CONNECT,
    m_OPTIONS,
    m_TRACE
} t_METHOD;

class RequestHandler {
public:
    RequestHandler(void);
//    RequestHandler(Server &serv, Request &req);
    ~RequestHandler(void);

    void initStatusCodeBook();
    void setStatusCode(int code);
    std::string getStatusCodeString();
    int getStatusCode();
    int getProtocolVersion() const;
    void setContentType(std::string path);
    std::string getContentType() const;
    std::string getBody() const;

    std::string getErrorPagePath();

    std::map<std::string, std::string> &getRequest(void);

    bool checkLastModified(std::string & path);

    void run(void);

    // Readings
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

    t_METHOD resolveMethod(std::string & method);

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
    std::string _default_error_file;

    std::string _content_type;
    std::string _body;
};

std::ostream &operator<<(std::ostream &out, RequestHandler &rh);

#endif