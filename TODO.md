# TODO

## LOCATION and CGI check
  [x] Cut uri in two with path (location) and file
  [] fournir la config de l'instance server dans la requestHandler class pour :
    [] verifier les locations par rapport methods allowed
    [] verifier si la requete porte sur un CGI (path valid)

## CGI, construire l'environnement avec le parsing de la requete (cle/valeur de la query string)
    [] Ajouter cgi type, interpreter and directory to config parsing class
    [] executer CGI script in a separate process and return the stdout (fork, pipe, dup2)
    [] create a html form for POST with python action and php action to test 2 differents CGI
        [] the python and php script could take the GET and POST and behave differently depending on the request 
            (GET: display the form and POST: display the result of the form)

## Body size limit
    [] test POST reqest body with the config client_body_limit

## Type of methods:
    [] if not GET, POST or DELETE: set the method UNKNOWN and set the error corresponding

## Files:
  [] UPLOAD a file: Upload file with a cgi post request
  [] DOWNLOAD a file: add a pdf file and a link to download it
  [] DELETE a file: DELETE request to delete file if location method allowed

[] comment and clean reponse/requestHandler classes

[] implement autoindex

