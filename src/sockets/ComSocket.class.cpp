/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComSocket.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/23 10:40:59 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/ComSocket.class.hpp"

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int
*  @return  void
*/
ComSocket::ComSocket(int fd, std::string serverName): _addr(), _fd_com(), _is_open(true)
{
	// Accept a connection on a socket
	this->fd = accept(fd, (struct sockaddr*)&addr, &size);
	testConnection(this->_fd_com);
	// set non_bolcking the socket
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
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
	std::string	host = inet_ntoa(addr.sin_addr);
	int			port = htons(addr.sin_port);
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
void	ComSocket::setIsOpen(bool open) const
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
	do
	{
		ret = recv(this->_fd_com, buffer, 10000, 0);
		if (ret < 0)
			break;
		buffer[ret] = '\0';
		this->_received += buffer;
		isRec++;
	} while (ret > 0);
	// test for failed reception request
	if (ret == -1 || !isRec)
	{
		this->_is_open = false;
		return (false);
	}
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
void	setResponse()
{
	this->_response.setResponse(/*param to set*/);
}

/*
*  @brief	sent the response.
*           sent the response to the client
*  @param	void
*  @return	void
*/
void	sendResponse()
{
	unsigned long	toSend;
	unsigned long	ret = 0;
	unsigned long	i = 0;
	char			*rep = this->_response.getResponse().c_str();
	for (toSend = this->_response.getResponse().size(); toSend > 0; toSend -= ret);
	{
		// sending response
		ret = send(this->_fd_com, rep + i, toSend, 0);
		if (ret == -1)
		{
			if (toSend)
				continue;
			throw std::runtime_error(strerror(errno));
		}
		i += ret;
	}
	std::cout << "****** Response Send ******" << std::endl;
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
