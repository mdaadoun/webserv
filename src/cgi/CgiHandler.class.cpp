#include "../../inc/cgi/CgiHandler.class.hpp"

/*
*  @brief   Default constructor. // temporarily
*  @param   void
*  @return  void
*/
CgiHandler::CgiHandler() {
    this->set_env();
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
CgiHandler::~CgiHandler() {}

/*
*  @brief   Assignment operator.
*           copy other request in this request
*  @param   CgiHandler &
*  @return  CgiHandler &
*/
CgiHandler	&CgiHandler::operator=(CgiHandler const &src)
{
    if (this != &src) {
        this->_env = src._env;
        this->_rawOutput = src._rawOutput;
    }
    return *this;
}

/*
*  @brief   Use Config, Request and Location to set the environment
*  @param   void
*  @return  void
*/
void		CgiHandler::set_env(void) {
//    std::map<std::string, std::string>	headers = _request.getHeaders();
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
}

/*
*  @brief   get the environment
*  @param   void
*  @return  std::map<std::string, std::string> &
*/
std::map<std::string, std::string> & CgiHandler::get_env(void) {
    return this->_env;
}


/*
*  @brief   execute the given script
*  @param   const std::string &script
*  @return  std::string
*/
std::string CgiHandler::executeCgi(const std::string &script) {
//    pid_t		pid;

//    char		**env;
    std::cout << "execute " << script << std::endl;

//    pid = fork();
//
//    if (pid == -1) {
//        std::cerr << "Status: 500";
//    }
//    else if (!pid) {
//        execve(scriptName.c_str(), NULL, env);
//    }
//    else {
//        waitpid(-1, NULL, 0);
//    }

    this->_rawOutput = "ERROR";
    return this->_rawOutput;
}


/*
*  @brief   Overloaded stream insertion operator
*  @param   std::ostream &out   the output stream (out)
*           CgiHandler &ch      a reference to a CgiHandler object
*  @return  std::ostream &
*/
std::ostream &operator<<(std::ostream &out, CgiHandler &ch) {
    std::map<std::string, std::string>::iterator it;
    out << "cgi_env\n";
    for (it = ch.get_env().begin(); it != ch.get_env().end(); it++) {
        out << it->first << " : " << it->second << std::endl;
    }
    return out;
}