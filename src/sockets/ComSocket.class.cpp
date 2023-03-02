/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComSocket.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/28 09:10:02 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/ComSocket.class.hpp"

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int
*  @return  void
*/
ComSocket::ComSocket(int fd, std::string serverName): _addr(), _fd_com(), _is_open(true), _is_send(false)
{
	// Accept a connection on a socket
	socklen_t	size = sizeof(this->_addr);
	this->_fd_com = accept(fd, (struct sockaddr*)&this->_addr, &size);
	testConnection(this->_fd_com, std::string("Error: communication not accept."));
	// set non_bolcking the socket
	if (fcntl(this->_fd_com, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error: set non-blocking ComSocket: " << serverName << std::endl;
		throw std::runtime_error(strerror(errno));
	}
	// set options in socket for reuse address
	int x = 1;
	int opt = setsockopt(this->_fd_com, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(x));
	testConnection(opt, std::string("Error: set option Comsocket."));
}

/*
*  @brief   Copy constructor.
*           copy other socket in this socket
*  @param   ComSocket &
*  @return  void
*/
ComSocket::ComSocket(ComSocket const &rhs)
{
	*this = rhs;
}

/*
*  @brief   Assignment operator.
*           copy other socket in this socket
*  @param   ComSocket &
*  @return  ComSocket &
*/
ComSocket	&ComSocket::operator=(ComSocket const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*  @brief	Get string IPP address .
*           return a string with address and port 
*  @param	void
*  @return	std::string
*/
std::string	ComSocket::getIPP() const
{
	std::string	host = inet_ntoa(this->_addr.sin_addr);
	int			port = htons(this->_addr.sin_port);
	std::ostringstream oss;
    oss << port;
	return (host + ':' + oss.str());
}

/*
*  @brief	Get fd.
*           return the file descrioptor of ComSocket
*  @param	void
*  @return	int
*/
int	ComSocket::getFdSocket() const
{
	return (this->_fd_com);
}

/*
*  @brief	Getter for _is_open.
*           Get the comsocket is open or not
*  @param	void
*  @return	bool
*/
bool	ComSocket::getIsOpen() const
{
	return (this->_is_open);
}


/*
*  @brief	Setter for _is_open.
*           set the comsocket at open or not
*  @param	bool
*  @return	void
*/
void	ComSocket::setIsOpen(bool open)
{
	this->_is_open = open;
}

/*
*  @brief	tester reception request.
*           Confirm  if request is received
*  @param	void
*  @return	bool
*/
bool ComSocket::isReceived()
{
	char	buffer[10001];
	int		isRec = 0;
	int		ret = 0;

	// reception of request
	bzero(buffer, 10000);
	while ((ret = recv(this->_fd_com, buffer, 10000, 0)) > 0)
	{
		buffer[ret] = '\0';
		this->_received += buffer;
		isRec++;
	}
	// test for failed reception request
	if (ret == 0 || !isRec)
	{
		this->_is_open = false;
		return (false);
	}
	// for debug
	std::cout << this->_received << std::endl;
	return (true);
}

/*
*  @brief	calling for parsing request.
*           
*  @param	void
*  @return	void
*/
void	ComSocket::parseRequest()
{
	this->_request.parsing(this->_received);
}

/*
*  @brief	set the response.
*           prepare the response
*  @param	void
*  @return	void
*/
void	ComSocket::setResponse()
{
	//to modify when parsing is done
	std::string	request(this->_received);
	this->_response.buildResponse(request);
}

/*
*  @brief	sent the response.
*           sent the response to the client
*  @param	void
*  @return	void
*/
void	ComSocket::sendResponse()
{
	unsigned long	toSend = this->_response.getResponse().size();
	long			ret = 0;
	unsigned long	i = 0;
	//const char		*rep = this->_response.getResponse().c_str();
	while (toSend > 0)
	{
		// sending response
		ret = send(this->_fd_com, &(this->_response.getResponse().c_str()[i]), toSend, 0);
		if (ret == -1)
		{
			if (toSend)
				continue;
			throw std::runtime_error(strerror(errno));
		}
		i += ret;
		toSend -= ret;
	}
	this->_is_send = true;
	std::cout << "****** Response Sent ******" << std::endl;
}

/*
*  @brief	reset all attributs.
*           clear and reset all for a new communication
*  @param	void
*  @return	void
*/
void	ComSocket::clear()
{
	//to modify when Respose class is implemented
	if (this->_is_send)
	{
		this->_is_open = false;
		return ;
	}
	else if (this->_is_open == false)
		return ;
	this->_is_open = true;
	this->_request.getRequest().clear();
	this->_response.getResponse().clear();
}

/*
*  @brief	Test _fd_com .
*           Confirm  data properly established
*  @param	int, std::string
*  @return	void
*/
void	ComSocket::testConnection(int data, std::string const &err)
{
	if (data < 0)
	{
		std::cout << err << std::endl;
		throw std::runtime_error(strerror(errno));
	}
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
ComSocket::~ComSocket()
{
	close(this->_fd_com);
	this->_fd_com = -1;
}
