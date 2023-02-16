# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 16:04:29 by fleblanc          #+#    #+#              #
#    Updated: 2023/02/16 10:31:39 by tlafont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Names

NAME	= webserv

# **************************************************************************** #
# Compilation

CC		= c++
WFLAGS	= -Wall -Wextra -Werror -Wpedantic
IFLAGS	= -I$(INCDIR)
OFLAGS	= -std=c++98 -g3

# **************************************************************************** #
# System commands

MKDIR	= mkdir -p
RM		= rm -rf

# **************************************************************************** #
# Directories

INCDIR	= inc
OBJDIR	= obj
SRCDIR	= src

# **************************************************************************** #
# List of source files

SRCNAME	= main.cpp \
		  parsing/parsing.cpp \
		  server/Server.class.cpp \
		  request/Request.class.cpp \
		  response/Response.class.cpp \
		  sockets/BindSocket.class.cpp \
		  sockets/ClientSocket.class.cpp \
		  sockets/ISocket.class.cpp \
		  sockets/ListenSocket.class.cpp

# **************************************************************************** #
# Variables where are listed source and object files

OBJ	= $(addprefix $(OBJDIR)/, $(SRCNAME:.cpp=.o))
SRC	= $(addprefix $(SRCDIR)/, $(SRCNAME))

# **************************************************************************** #
# Extra

BASENAME	= `basename $(PWD)`
CR			= "\r"$(CLEAR)
CLEAR		= "\\033[0K"
EOC			= "\033[0;0m"
GREY		= "\033[0;30m"
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"
YELLOW		= "\033[0;33m"
BLUE		= "\033[0;34m"
PURPLE		= "\033[0;35m"
CYAN		= "\033[0;36m"
WHITE		= "\033[0;37m"

# **************************************************************************** #
# Rules

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
		@$(MKDIR) $(dir $@)
		@$(CC) $(WFLAGS) $(OFLAGS) $(IFLAGS) -c $< -o $@
		@printf $(CR)"[ $(BASENAME)/%s ]"$(CLEAR) $@

all:	$(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(WFLAGS) $(OFLAGS) $(OBJ) -o $(NAME)
		@printf $(CR)$(GREEN)"✓ $(NAME) is created\n"$(EOC)

clean:
		@if [ -d $(OBJDIR) ]; then \
			$(RM) $(OBJDIR) \
			&& printf $(CR)$(YELLOW)"✗ The objects files of $(NAME) " \
			&& printf "are cleaned\n"$(EOC); \
		fi

fclean:	clean
		@if [ -e $(NAME) ]; then \
			$(RM) $(NAME) \
			&& printf $(CR)$(RED)"✗ $(NAME) is cleaned\n"$(EOC); \
		fi

re:	fclean all

.PHONY:	all clean fclean re
