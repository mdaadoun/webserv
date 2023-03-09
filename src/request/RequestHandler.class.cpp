
#include "../../inc/request/RequestHandler.class.hpp"

/*
*  @brief   Main constructor. Join the request and the config together.
*  @param   void
*  @return  void
*/
RequestHandler::RequestHandler(Request const & req, Config *conf) {
    this->_status_code = req.getStatus();
    this->_request_method = req.getMethod();
    this->_request_location = req.getUri().first;
    this->_request_file = req.getUri().second;
    this->_protocol_version = "HTTP/1.1";

    this->_request_IfModifiedSince = "Wed, 28 Feb 2022 15:27:00 GMT"; // replace with a getter

    this->_files_root = conf->getRoot();
    this->_index_file = conf->getIndex();
    this->_locations = conf->getLocations();
    this->_cgi_list = conf->getCgi();
    this->_errorPages = conf->getErrorPages();
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
RequestHandler::~RequestHandler() {}

bool RequestHandler::checkLastModified(std::string & path) {
    std::string if_modified_since_str = this->_request_IfModifiedSince;

    if (if_modified_since_str.length() > 0) {
        struct tm if_modified_since_tm;
        memset(&if_modified_since_tm, 0, sizeof(if_modified_since_tm));
        strptime(if_modified_since_str.c_str(), "%a, %d %b %Y %H:%M:%S %Z", &if_modified_since_tm);
        time_t if_modified_since_time = mktime(&if_modified_since_tm);
        struct stat file_stat;
        memset(&file_stat, 0, sizeof(file_stat));
        stat(path.c_str(), &file_stat);
        time_t last_modified_time = file_stat.st_mtime;
        double time_diff = difftime(last_modified_time, if_modified_since_time);
        if (time_diff <= 0)
            return true;
    }
    return false;
}

std::string RequestHandler::readContent(std::string & path) {
    std::ofstream		file;
    std::stringstream	buffer;

    file.open(path.c_str(), std::ifstream::in);
    if (file.is_open() == false) {
        this->setStatusCode(404);
    }
    if (this->getStatusCode() == 200 && checkLastModified(path))
        this->setStatusCode(304);
    else
        buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void RequestHandler::setContentType(std::string path)
{
    std::string file = this->_request_file;
    std::string type = path.substr(path.rfind(".") + 1, path.size() - path.rfind("."));
    if (type == "html")
        _content_type = "text/html";
    else if (type == "css")
        _content_type = "text/css";
    else if (type == "js")
        _content_type = "text/javascript";
    else if (type == "svg" || type == "xml")
        _content_type = "image/svg+xml";
    else if (type == "jpeg" || type == "jpg")
        _content_type = "image/jpeg";
    else if (type == "png")
        _content_type = "image/png";
    else if (type == "bmp")
        _content_type = "image/bmp";
    else if (type == "ico")
        _content_type = "image/x-icon";
    else
        _content_type = "text/plain";
}

/*
*  @brief   get the corresponding file of the status code
 *          if the file doesnt open, fall back on default error.html
*  @param   void
*  @return  std::string file path
*/
std::string RequestHandler::getErrorPagePath() {
    std::ofstream		file;
    std::string path = this->_files_root + "/";
    std::map<std::string, std::string>::iterator it;
    for (it = _errorPages.begin(); it != _errorPages.end(); ++it) {
        int error = std::atoi(it->first.substr(it->first.size() - 3).c_str());
        if (error == this->getStatusCode()) {
            path += it->second;
        }
    }
    file.open(path.c_str(), std::ifstream::in);
    if (file.is_open() == false) {
        path = this->_files_root + "/error.html";
    }
    file.close();
    return path;
}

/*
*  @brief   run the get method
 *          check first if the path is root / to get the index page
 *          check then what it the content type (html, txt, binary)
 *              this->setContentType(path);
 *          if the content is html, read the file content with readHTML(path);
 *          check if there is an error code and get the corresponding page.
 *              4**.html or 5**.html file, fall back on the error.html page if problem.
 *          empty the body if 304 Not modified.
*  @param   void
*  @return  void
*/
void RequestHandler::runGETMethod() {
    std::string         path;

    if (this->getRequestURI() == "/") {
        // Check if there is autoindex, else it is a 404 ?
        path = this->_files_root + this->getRequestURI() + this->_index_file;
    } else {
        path = this->_files_root + this->getRequestURI();
    }
    this->setContentType(path);
    this->_body = readContent(path);
}

/*
*  @brief   run the head method, same as get but don't create a body
*  @param   void
*  @return  void
*/
void RequestHandler::runHEADMethod() {
    this->runGETMethod();
    this->_body = "";
}

void RequestHandler::runDELETEMethod() {
    std::cout << "run the Delete method" << std::endl;
}

void RequestHandler::runPOSTMethod() {
    std::cout << "run the Post method" << std::endl;
}

bool checkIfMethod(std::string allowed_methods, std::string request_method) {
    std::stringstream ss(allowed_methods);
    std::vector<std::string> methods;
    std::string method;
    while (std::getline(ss, method, ' ')) {
        methods.push_back(method);
    }
    for (std::vector<std::string>::size_type i = 0; i < methods.size(); ++i) {
        if (methods[i] == request_method)
            return true;
    }
    return false;
}

/*
*  @brief   get route and check with config locations method permissions
 *          loc string is used to remove the trailing / in path to fix the checking
*  @param   void
*  @return  bool, true if method is allowed, else false
*/
bool RequestHandler::checkIfMethodIsAllowed() {
    std::map<std::basic_string<char>, std::map<std::basic_string<char>, std::basic_string<char> > >::const_iterator it;
    std::map<std::basic_string<char>, std::basic_string<char> >::const_iterator inner_it;

    for(it = _locations.begin(); it != _locations.end(); ++it) {
        std::string loc = this->getRequestLocation();
        if (!loc.empty() && loc[loc.length() - 1] == '/') {
            loc.erase(loc.length() - 1);
        }
        if (this->getRequestLocation() == it->first || loc == it->first) {
            for(inner_it = it->second.begin(); inner_it != it->second.end(); ++inner_it) {
                if (inner_it->first == "allow_methods") {
                    if (checkIfMethod(inner_it->second, this->getMethod())) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/*
*  @brief   check if the request file and location is a correct cgi config
*  @param   void
*  @return  bool after check
*/
bool RequestHandler::checkIfCGI() {
    std::map<std::string, std::map<std::string, std::string> >::iterator it;
    std::string file = this->_request_file;
    if (file.size()) {
        std::string type = file.substr(file.rfind("."), file.size() - file.rfind("."));
        for (it = _cgi_list.begin(); it != _cgi_list.end(); ++it) {
            std::string key = it->first;
            std::map<std::string, std::string>::iterator inner_it;
            bool cgi = false;
            for (inner_it = it->second.begin(); inner_it != it->second.end(); ++inner_it) {
                if (inner_it->first == "file" && inner_it->second == type) {
                    cgi = true;
                }
            }
            if (cgi) {
                for (inner_it = it->second.begin(); inner_it != it->second.end(); ++inner_it) {
                    if (inner_it->first == "directory") {
                        std::string test = this->_request_location;
                        if (test.size() && test.at(0) == '/') {
                            test.erase(0, 1);
                        }
                        if (test.size() && test.at(test.size() - 1) == '/') {
                            test.erase(test.length() - 1, 1);
                        }
                        if (test != inner_it->second)
                            return false;
                    } else if (inner_it->first == "interpreter") {
                        this->_cgi_interpreter = inner_it->second;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

/*
*  @brief   run the request method to each possibilities
 *          check first if the method is allowed to the given location
 *          check if it is a cgi script
 *          deal with static files
*  @param   void
*  @return  void
*/
void RequestHandler::run(void) {
    if (this->checkIfMethodIsAllowed()) {
        if (this->checkIfCGI()) {
            CgiHandler cgi(*this);
            this->_body = cgi.executeCgi();
        } else {
            switch (RequestHandler::resolveMethod(this->_request_method)) {
                case GET:
                    this->runGETMethod();
                    break;
                case HEAD:
                    this->runHEADMethod();
                    break;
                case POST:
                    this->runPOSTMethod();
                    break;
                case DELETE:
                    this->runDELETEMethod();
                    break;
//            case PUT:
//                std::cout << "run the Put method" << std::endl;
//                break;
//            case CONNECT:
//                std::cout << "run the Connect method" << std::endl;
//                break;
//            case OPTIONS:
//                std::cout << "run the Options method" << std::endl;
//                break;
//            case TRACE:
//                std::cout << "run the Put method" << std::endl;
//                break;
                default:
                    std::cout << "UNKNOWN method, set error here ?" << std::endl;
            }
        }
    } else {
        this->setStatusCode(405);
    }

    if (this->getStatusCode() != 200) {
        std::string path = getErrorPagePath();
        this->setContentType(path);
        this->_body = readContent(path);
    }

//    if (this->getStatusCode() == 304)
//        this->_body = "";
}

m_METHOD RequestHandler::resolveMethod(std::string &met) {
    if (met == "GET")
        return GET;
    else if (met == "HEAD")
        return HEAD;
    else if (met == "POST")
        return POST;
    else if (met == "DELETE")
        return DELETE;
//    else if (met == "PUT")
//        return PUT;
//    else if (met == "CONNECT")
//        return CONNECT;
//    else if (met == "OPTIONS")
//        return OPTIONS;
//    else if (met == "TRACE")
//        return TRACE;
    else
        return ERROR;
}


std::string RequestHandler::getProtocolVersion() const {
    return this->_protocol_version;
}

// move to utils
std::string RequestHandler::getDate() {
    std::string date;
    time_t now_time = std::time(NULL);
    struct tm *now = std::localtime(&now_time);
    std::stringstream ss;
	std::string weekday[7] = {"Mon",
                              "Tue",
                              "Wed",
                              "Thu",
                              "Fri",
                              "Sat",
                              "Sun"};
    std::string month[12] = {"Jan",
                             "Feb",
                             "Mar",
                             "Apr",
                             "May",
                             "Jun",
                             "Jul",
                             "Aug",
                             "Sep",
                             "Oct",
                             "Nov",
                             "Dec"};
	date += weekday[now->tm_wday];
	date += ", ";
    ss << now->tm_mday;
	date += ss.str();
    ss.clear();
    ss.str("");
	date += " ";
	date += month[now->tm_mon];
	date += " ";
    ss << now->tm_year;
	date += ss.str();
    ss.clear();
    ss.str("");
	date += " ";
    ss << now->tm_hour;
    date += ss.str();
    ss.clear();
    ss.str("");
	date += ":";
    ss << now->tm_min;
    date += ss.str();
    ss.clear();
    ss.str("");
	date += ":";
    ss << now->tm_sec;
    date += ss.str();
    ss.clear();
    ss.str("");
	date += " ";
    ss << now->tm_zone;
    date += ss.str();
    ss.clear();
    ss.str("");
    return date;
}

std::string RequestHandler::getRequestLocation() const {
    return this->_request_location;
}

std::string RequestHandler::getRequestFile() const {
    return this->_request_file;
}

std::string RequestHandler::getRoot() const {
    return this->_files_root;
}

std::string RequestHandler::getMethod() const {
    return this->_request_method;
}

std::string RequestHandler::getRequestURI() const {
    return this->_request_location + this->_request_file;
}

void RequestHandler::setStatusCode(int sc) {
    this->_status_code = sc;
}

int RequestHandler::getStatusCode() {
    return this->_status_code;
}

std::string RequestHandler::getCgiInterpreter() const {
    return this->_cgi_interpreter;
}

// move to utils
std::string RequestHandler::getStatusCodeString() {
    this->_status_code_registry[100] = "100 Continue";
    this->_status_code_registry[101] = "101 Switching Protocols";
    this->_status_code_registry[200] = "200 OK";
    this->_status_code_registry[201] = "201 Created";
    this->_status_code_registry[202] = "202 Accepted";
    this->_status_code_registry[203] = "203 Non-Authoritative Information";
    this->_status_code_registry[204] = "204 No Content";
    this->_status_code_registry[205] = "205 Reset Content";
    this->_status_code_registry[206] = "206 Partial Content";
    this->_status_code_registry[300] = "300 Multiple Choices";
    this->_status_code_registry[301] = "301 Moved Permanently";
    this->_status_code_registry[302] = "302 Found";
    this->_status_code_registry[303] = "303 See Other";
    this->_status_code_registry[304] = "304 Not Modified";
    this->_status_code_registry[305] = "305 Use Proxy";
    this->_status_code_registry[307] = "307 Temporary Redirect";
    this->_status_code_registry[400] = "400 Bad Request";
    this->_status_code_registry[401] = "401 Unauthorized";
    this->_status_code_registry[402] = "402 Payment Required";
    this->_status_code_registry[403] = "403 Forbidden";
    this->_status_code_registry[404] = "404 Not Found";
    this->_status_code_registry[405] = "405 Method Not Allowed";
    this->_status_code_registry[406] = "406 Not Acceptable";
    this->_status_code_registry[407] = "407 Proxy Authentication Required";
    this->_status_code_registry[408] = "408 Request Time-out";
    this->_status_code_registry[409] = "409 Conflict";
    this->_status_code_registry[410] = "410 Gone";
    this->_status_code_registry[411] = "411 Length Required";
    this->_status_code_registry[412] = "412 Precondition Failed";
    this->_status_code_registry[413] = "413 Request Entity Too Large";
    this->_status_code_registry[414] = "414 Request-URI Too Large";
    this->_status_code_registry[415] = "415 Unsupported Media Type";
    this->_status_code_registry[416] = "416 Requested range not satisfiable";
    this->_status_code_registry[417] = "417 Expectation Failed";
    this->_status_code_registry[500] = "500 Internal Server Error";
    this->_status_code_registry[501] = "501 Not Implemented";
    this->_status_code_registry[502] = "502 Bad Gateway";
    this->_status_code_registry[503] = "503 Service Unavailable";
    this->_status_code_registry[504] = "504 Gateway Time-out";
    this->_status_code_registry[505] = "505 HTTP Version not supported";
    std::string sc = this->_status_code_registry[this->_status_code];
    return (sc);
}

std::string RequestHandler::getContentType(void) const{
    return this->_content_type;
}

std::string RequestHandler::getBody(void) const{
    return this->_body;
}

/*
*  @brief   Overloaded stream insertion operator
*  @param   std::ostream &out   the output stream (out)
*           RequestHandler &rh  a reference to a RequestHandler object
*  @return  std::ostream &
*/
std::ostream &operator<<(std::ostream &out, RequestHandler &rh) {
    std::map<std::string, std::string>::iterator it;
    out << "results after handling:\n";
    out << "Content Type:" << rh.getContentType() << std::endl;
    out << "Status Code:" << rh.getStatusCodeString() << std::endl;
    out << "Body:" << rh.getBody() << std::endl;
    return out;
}

