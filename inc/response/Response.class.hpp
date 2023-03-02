#pragma once
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "../request/RequestHandler.class.hpp"
#include "../request/Request.class.hpp"



class Response
{
	public:
		//---- canonical form ----//
			// constructors //
		Response();

			// destructor //
		~Response();

		//---- getter ----//
        std::string getResponse(void) const;

		//---- member methods ----//
		void	buildResponse(Request const & req);
//		void	addBodyResponse(std::string& path);
	
	private:
		std::string		_response;

		Response	&operator=(Response const &rhs);
};

std::ostream &operator<<(std::ostream &out, Response &rh);

#endif
