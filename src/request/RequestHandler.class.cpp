
#include "../../inc/request/RequestHandler.class.hpp"

/*
*  @brief   Default constructor.
*  @param   void
*  @return  void
*/
RequestHandler::RequestHandler(void) {
    this->_request["Method"] = "HEAD";
    this->_request["Path"] = "/";
    this->_request["If-Modified-Since"] = "Wed, 21 Oct 2015 07:28:00 GMT";

    this->_response["Status-code"] = "200 OK";
    this->_response["Protocol-version"] = "HTTP/1.1";
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
RequestHandler::~RequestHandler() {}


std::map<std::string, std::string> &RequestHandler::get_request(void){
    return this->_request;
}

void RequestHandler::getMethod() {
    std::cout << "run the Get method" << std::endl;
    // check if this->_request["Path"] is a correct file, if yes get body and send 200 OK
    // check if header If-Modified-Since else it is 304 answer
    // else 404 error with 404.html error page
}

void RequestHandler::headMethod() {
    std::cout << "run the Head method" << std::endl;
    // check if this->_request["Path"] is a correct file, if yes send 200 OK without body
    // check if header If-Modified-Since else it is 304 answer
    // else 404 error
}

/*
*  @brief   run the request method to each possibilities
*  @param   void
*  @return  void
*/
void RequestHandler::run(void) {
    switch (RequestHandler::resolve_method(this->_request["Method"])) {
        case m_GET:
            this->getMethod();
            break;
        case m_POST:
            std::cout << "run the Post method" << std::endl;
            break;
        case m_HEAD:
            this->headMethod();
            break;
        case m_DELETE:
            std::cout << "run the delete method" << std::endl;
            break;
        case m_PUT:
            std::cout << "run the Put method" << std::endl;
            break;
        case m_CONNECT:
            std::cout << "run the Connect method" << std::endl;
            break;
        case m_OPTIONS:
            std::cout << "run the Options method" << std::endl;
            break;
        case m_TRACE:
            std::cout << "run the Put method" << std::endl;
            break;
        default:
            std::cout << "Not a known method, error ?" << std::endl;
    }
}

t_METHOD RequestHandler::resolve_method(std::string &met) {
    if (met == "GET")
        return m_GET;
    else if (met == "HEAD")
        return m_HEAD;
    else if (met == "POST")
        return m_POST;
    else if (met == "DELETE")
        return m_DELETE;
    else if (met == "PUT")
        return m_PUT;
    else if (met == "CONNECT")
        return m_CONNECT;
    else if (met == "OPTIONS")
        return m_OPTIONS;
    else if (met == "TRACE")
        return m_TRACE;
    else
        return m_ERROR;
}


/*
*  @brief   Overloaded stream insertion operator
*  @param   std::ostream &out   the output stream (out)
*           RequestHandler &rh  a reference to a RequestHandler object
*  @return  std::ostream &
*/
std::ostream &operator<<(std::ostream &out, RequestHandler &rh) {
    std::map<std::string, std::string>::iterator it;
    out << "request:\n";
    for (it = rh.get_request().begin(); it != rh.get_request().end(); it++) {
        out << it->first << " : " << it->second << std::endl;
    }
    out << "result after handling:\n";
    return out;
}

