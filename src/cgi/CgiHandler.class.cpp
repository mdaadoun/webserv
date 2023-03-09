#include "../../inc/cgi/CgiHandler.class.hpp"

/*
*  @brief   Default constructor.
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
*  @brief   Set the environment variables
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
//    this->_env["REQUEST_METHOD"] = _request.getMethod();
//    this->_env["CONTENT_LENGTH"] = this->_body.length() as string;
//    this->_env["CONTENT_TYPE"] = ;
//    this->_env["PATH_INFO"] = _request.getRequestLocation();
//    this->_env["PATH_TRANSLATED"] = _request.getRequestLocation();
//    this->_env["QUERY_STRING"] = _request.getQueryString();
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
*  @return  std::map<std::string, std::string> &
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
*  @return  std::map<std::string, std::string> &
*/
std::map<std::string, std::string> & CgiHandler::get_env(void) {
    return this->_env;
}

/*
*  @brief   execute the given script and return the output
*  @param   const std::string &script
*  @return  std::string
*/
std::string CgiHandler::executeCgi() {
    pid_t		pid;
    // Save the current stdin and stdout file descriptors
//    int			saveStdin, saveStdout;
//    saveStdin = dup(STDIN_FILENO);
//    saveStdout = dup(STDOUT_FILENO);

//    FILE	*fIn = tmpfile();
//    FILE	*fOut = tmpfile();
//    long	fdIn = fileno(fIn);
//    long	fdOut = fileno(fOut);
//    write(fdIn, _body.c_str(), _body.size());
//    lseek(fdIn, 0, SEEK_SET);

//    // Create pipes for stdin and stdout redirection solution 2 ?
//    int pipeIn[2], pipeOut[2];
//    pipe(pipeIn);
//    pipe(pipeOut);

    char		**env = get_env_char();
    pid = fork();
    if (pid == -1) {
        std::cout << "Fork crashed. Error 500." << std::endl;
    } else if (!pid) {
        char *const args[] = { const_cast<char*>(this->_cgi_interpreter.c_str()),
                               const_cast<char*>(this->_script.c_str()), NULL };
//        dup2(fdIn, STDIN_FILENO);
//        dup2(fdOut, STDOUT_FILENO);

//        // Redirect stdin and stdout to the pipes
//        dup2(pipeIn[0], STDIN_FILENO);
//        dup2(pipeOut[1], STDOUT_FILENO);
//
//        // Close the unused ends of the pipes
//        close(pipeIn[1]);
//        close(pipeOut[0]);
//
//        // Write the request body to stdin
//        write(pipeIn[1], _body.c_str(), _body.size());
//        lseek(pipeIn[1], 0, SEEK_SET);

        std::cout << "Execute" <<  this->_cgi_interpreter << std::endl;
        execve(this->_cgi_interpreter.c_str(), args, env);
        std::cerr << "Execve Error 500." << std::endl;
    } else {
//        char	buffer[] = {0};

        waitpid(-1, NULL, 0);
//        lseek(fdOut, 0, SEEK_SET);

//        int ret = 1;
//        while (ret > 0)
//        {
//            memset(buffer, 0, 1024);
//            ret = read(fdOut, buffer, 1024 - 1);
//            this->_body += buffer;
//        }
    }

//    dup2(saveStdin, STDIN_FILENO);
//    dup2(saveStdout, STDOUT_FILENO);
//    fclose(fIn);
//    fclose(fOut);
//    close(fdIn);
//    close(fdOut);
//    close(saveStdin);
//    close(saveStdout);

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