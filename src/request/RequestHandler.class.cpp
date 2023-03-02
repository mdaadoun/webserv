
#include "../../inc/request/RequestHandler.class.hpp"

/*
*  @brief   Default constructor. // Temporary will move to a Server config+request constructor
*  @param   void
*  @return  void
*/
RequestHandler::RequestHandler(Request const & req) {
    this->_status_code = req.getStatus();
    this->_request["Method"] = req.getMethod();
    this->_request["URI"] = req.getUri();
    this->_protocol_version = "HTTP/1.1";
    this->_request["If-Modified-Since"] = "Wed, 28 Feb 2022 15:27:00 GMT";

    // need also the server config to get those :
    this->_files_root = "./www/html";
    this->_index_file = "index.html";
    this->_400_file = "400.html";
    this->_404_file = "404.html";
    this->_500_file = "500.html";
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
RequestHandler::~RequestHandler() {}


std::map<std::string, std::string> &RequestHandler::getRequest(void){
    return this->_request;
}


bool RequestHandler::checkLastModified(std::string & path) {
    std::string if_modified_since_str = this->_request["If-Modified-Since"];

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

std::string RequestHandler::getErrorPagePath() {
    std::ofstream		file;
    std::string path = this->_files_root + "/";
    switch (this->getStatusCode()) {
        case(400):
            path += this->_400_file;
            break;
        case(401):
            path += this->_401_file;
            break;
        case(403):
            path += this->_403_file;
            break;
        case(404):
            path += this->_404_file;
            break;
        case(405):
            path += this->_405_file;
            break;
        case(410):
            path += this->_410_file;
            break;
        case(413):
            path += this->_413_file;
            break;
        case(500):
            path += this->_500_file;
            break;
        case(503):
            path += this->_503_file;
            break;
        default:
            break;
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
void RequestHandler::getMethod() {
    std::map<std::string, std::string> req = this->getRequest();
    std::string         path;

    if (req["URI"] == "/") {
        path = this->_files_root + req["URI"] + this->_index_file;
    } else {
        path = this->_files_root + req["URI"];
    }
    this->setContentType(path);
    this->_body = readContent(path);

    if (this->getStatusCode() >= 400) {
        path = getErrorPagePath();
        this->setContentType(path);
        this->_body = readContent(path);
    }

//    if (this->getStatusCode() == 304)
//        this->_body = "";
}

/*
*  @brief   run the head method, same as get but don't create a body
*  @param   void
*  @return  void
*/
void RequestHandler::headMethod() {
    this->getMethod();
    this->_body = "";
}

void RequestHandler::deleteMethod() {
    std::cout << "run the Delete method" << std::endl;
}

void RequestHandler::postMethod() {
    std::cout << "run the Post method" << std::endl;
}

/*
*  @brief   run the request method to each possibilities
*  @param   void
*  @return  void
*/
void RequestHandler::run(void) {
    switch (RequestHandler::resolveMethod(this->_request["Method"])) {
        case GET:
            this->getMethod();
            break;
        case HEAD:
            this->headMethod();
            break;
        case POST:
            std::cout << "run the Post method" << std::endl;
            break;
        case DELETE:
            std::cout << "run the delete method" << std::endl;
            break;
        case PUT:
            std::cout << "run the Put method" << std::endl;
            break;
        case CONNECT:
            std::cout << "run the Connect method" << std::endl;
            break;
        case OPTIONS:
            std::cout << "run the Options method" << std::endl;
            break;
        case TRACE:
            std::cout << "run the Put method" << std::endl;
            break;
        default:
            std::cout << "Not a known method, error ?" << std::endl;
    }
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
    else if (met == "PUT")
        return PUT;
    else if (met == "CONNECT")
        return CONNECT;
    else if (met == "OPTIONS")
        return OPTIONS;
    else if (met == "TRACE")
        return TRACE;
    else
        return ERROR;
}


std::string RequestHandler::getProtocolVersion() const {
    return this->_protocol_version;
}

// DATE GENERATION TO FIX
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

int RequestHandler::getStatusCode() {
    return this->_status_code;
}

void RequestHandler::setStatusCode(int sc) {
    this->_status_code = sc;
}

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
    out << "request:\n";
    for (it = rh.getRequest().begin(); it != rh.getRequest().end(); it++) {
        out << it->first << " : " << it->second << std::endl;
    }
    out << "results after handling:\n";

    out << "Content Type:" << rh.getContentType() << std::endl;
    out << "Status Code:" << rh.getStatusCodeString() << std::endl;
    out << "Body:" << rh.getBody() << std::endl;
    return out;
}

