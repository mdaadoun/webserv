# TODO

## CGI parsing
* [X] Add a config parsing class multiple cgi :
* [X] 'cgi-bin' is default cgi directory if not given
* [ ] Add a default location if no location given, default is '/' with only 'GET' method allowed

## REQUEST
* [ ] to void	ComSocket::setResponse(), pass the config of the current server to build the response
  * this->_response.buildResponse(this->_request, this->_config);

## LOCATION and CGI check
* [ ] In the requestHandler, if after the request parsing status code is 200 :
  * [ ] Check if method is allowed to the requested path/route location
  * [ ] Check if the file is of CGI type (POST method is only for cgi file)
    * [ ] Else go on with static files reading (improve GET DELETE method with error gestion)
* [x] Cut uri in two with path (location) and file
  * [ ] fournir la config de l'instance server dans la requestHandler class pour :
    * [ ] verifier les locations par rapport methods allowed
    * [ ] verifier si la requete porte sur un CGI (path valid)

## CGI
* [ ] construire l'environnement avec le parsing de la requete (cle/valeur de la query string)
* [ ] executer CGI script in a separate process and return the stdout (fork, pipe, dup2)
* [ ] create a html form for POST with python action and php action to test 2 differents CGI
    * [ ] the python and php script could take the GET and POST and behave differently depending on the request 
          (GET: display the form and POST: display the result of the form)

## Body size limit
* [ ] test POST reqest body with the config client_body_limit
  * [ ] define a default value if not set
  * u_long _max_size; (Server.class.hpp)

## Type of methods:
* [ ] if not GET, POST or DELETE: set the method UNKNOWN and set the error corresponding

## Files:
* [ ] UPLOAD a file: Upload file with a cgi post request
* [ ] DOWNLOAD a file: add a pdf file and a link to download it
* [ ] DELETE a file: DELETE request to delete file if location method allowed

## Cookie and Session
* In the response, add to the header a cookie
* In the response, get and set the session id

## Others:
* [ ] implement autoindex (in config file, default is autoindex=off) (check what correct behavior is expected with it, is it really asked by the subject ?)
* [ ] comment and clean reponse/requestHandler classes
* [ ] Server output cleaning, add a timestamp and a clear INFO message 

## To Fix:
* [ ] RequestHandler::checkLastModified(), doesn't work anymore, should give a 304 Not Modified depending date diff
* [ ] RequestHandler::getDate(), the date format is not correct

## Cleaning:
* Request class -> could be renamed RequestParsing
* the server could use a format to each info console output : TIMESTAMP SERVER_NAME INFO (white, green, red colors for info, success and error)

## Tests:
* [ ] Comprendre et manipuler le tester fourni : ubuntu_tester et ubuntu_cgi_tester
* [ ] Siege et stress test ? (voir bareme de correction)
  * [ ] chrome + firefox usage entraine un double free (doit on vraiment gerer deux client en meme temps, dans le bareme de correction
  "use reference browser of the team" et dans le sujet "Your server must be compatible with the web browser of your choice.")
