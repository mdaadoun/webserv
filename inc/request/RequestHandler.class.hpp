
#pragma once
#ifndef HANDLE_REQUEST_HPP
#define HANDLE_REQUEST_HPP

# include <iostream>
# include <map>

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
//    RequestHandler(Request &req);
    ~RequestHandler(void);

//    void set_status_code(int code);
//    int get_status_code() const;

    std::map<std::string, std::string> &get_request(void);

    void run();
    // Methods
    void getMethod();
    void headMethod();

    t_METHOD resolve_method(std::string & method);

private:
    std::map<std::string, std::string> _request;
    std::map<std::string, std::string> _response;
    std::map<std::string, std::string> _status_code_book;
//    int _status_code;
//    const std::string _protocol_version;
};

std::ostream &operator<<(std::ostream &out, RequestHandler &rh);

#endif