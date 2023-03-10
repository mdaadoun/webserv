#pragma once
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "../request/RequestHandler.class.hpp"
#include "../request/Request.class.hpp"
#include "../parsing/Parsing.hpp"

class Response
{
	public:
        // constructor and destructor
		Response();
		~Response();

		//---- getter ----//
        std::string getResponse(void) const;

		//---- member methods ----//
		void	buildResponse(Request const & req, Config * config);
	private:
        Response	&operator=(Response const &rhs);
		std::string		_response;
};

std::ostream &operator<<(std::ostream &out, Response &rh);

#endif
