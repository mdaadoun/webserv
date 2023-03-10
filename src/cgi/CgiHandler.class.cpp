#include "../../inc/cgi/CgiHandler.class.hpp"


// parsing std::map<std::string, std::string> to string
std::string recomposeQueryString(std::map<std::string, std::string> &query) {
    std::ostringstream oss;
    for (std::map<std::string, std::string>::iterator it = query.begin(); it != query.end(); ++it) {
        if (it != query.begin()) {
            oss << "&";
        }
        oss << it->first << "=" << it->second;
    }
    std::cout << oss.str() << std::endl;
    return (oss.str());
}

/*
*  @brief   Default constructor.
 *          Get the needed data to set the execution.
*  @param   void
*  @return  void
*/
CgiHandler::CgiHandler(RequestHandler const & rh) {
    char currentDir[1024];
    getcwd(currentDir, sizeof(currentDir));
    std::string root = rh.getRoot();
    if (!root.empty() && root[0] == '.') {
        root = root.substr(1);
    }
    this->_script = currentDir + root + rh.getRequestURI();
    this->_cgi_interpreter = rh.getCgiInterpreter();
    std::map<std::string, std::string> tmp = rh.getQueryString();
    this->_query_string = recomposeQueryString(tmp);
    this->_method = rh.getMethod();
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
    }
    return *this;
}

/*
*  @brief   Set the environment variables needed for execve
*  @param   void
*  @return  void
*/
void		CgiHandler::set_env(void) {
    // https://fr.wikipedia.org/wiki/Variables_d%27environnement_CGI
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    this->_env["SERVER_SOFTWARE"] = "webserv/1.0";
    this->_env["REDIRECT_STATUS"] = "200";
    this->_env["SCRIPT_NAME"] = this->_script;
    this->_env["SCRIPT_FILENAME"] = this->_script;
    this->_env["REQUEST_METHOD"] = this->_method;
//    this->_env["CONTENT_LENGTH"] = this->_body.length() as string;
//    this->_env["CONTENT_TYPE"] = ;
//    this->_env["PATH_INFO"] = _request.getRequestLocation();
//    this->_env["PATH_TRANSLATED"] = _request.getRequestLocation();
    this->_env["QUERY_STRING"] = this->_query_string;
//    this->_env["REMOTE_ADDR"] = ?;
//    this->_env["REMOTE_IDENT"] = ?;
//    this->_env["REMOTE_USER"] = ?;
//    this->_env["REQUEST_URI"] = _request.getRequestURI(); //missing probably the query string
//    this->_env["SERVER_NAME"] = ?;
//    this->_env["SERVER_PORT"] = ?;
}

/*
*  @brief   get the environment as a char * for execve
*  @param   void
*  @return  char ** env
*/
char **CgiHandler::get_env_char(void) {

    char	**env = new char*[this->_env.size() + 1];
    int	j = 0;
    for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
        std::string	element = i->first + "=" + i->second;
        env[j] = new char[element.size() + 1];
        env[j] = strcpy(env[j], (const char*)element.c_str());
        j++;
    }
    env[j] = NULL;
    return env;
}

/*
*  @brief   get the environment
*  @param   void
*  @return  std::map<std::string, std::string> & _env
*/
std::map<std::string, std::string> & CgiHandler::get_env(void) {
    return this->_env;
}

/*
*  @brief   execute the given script and return the output
*  @param   void
*  @return  std::string body
*/
std::string CgiHandler::executeCgi() {
    pid_t		pid;
    int pipeIn[2], pipeOut[2];
    pipe(pipeIn);
    pipe(pipeOut);

    char		**env = get_env_char();
    pid = fork();
    if (pid == -1) {
        std::cout << "Fork crashed. Error 500." << std::endl;
    } else if (!pid) {
        char *const args[] = { const_cast<char*>(this->_cgi_interpreter.c_str()),
                               const_cast<char*>(this->_script.c_str()), NULL };

        std::cout << this->_cgi_interpreter << ", " << this->_script << std::endl;
        close(pipeIn[1]);
        dup2(pipeIn[0], STDIN_FILENO);
        close(pipeIn[0]);
        close(pipeOut[0]);
        dup2(pipeOut[1], STDOUT_FILENO);
        close(pipeOut[1]);

        execve(this->_cgi_interpreter.c_str(), args, env);
        std::cerr << "Execve failed, Error 500." << std::endl;
    } else {
        close(pipeIn[0]);
        close(pipeOut[1]);
        char	buffer[1024];
        waitpid(pid, NULL, 0);

        int ret = 1;
        while (ret > 0)
        {
            memset(buffer, 0, 1024);
            ret = read(pipeOut[0], buffer, 1024 - 1);
            this->_body += buffer;
        }
    }

    for (size_t i = 0; env[i]; i++)
        delete[] env[i];
    delete[] env;

    if (!pid)
        exit(0);

    return this->_body;
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