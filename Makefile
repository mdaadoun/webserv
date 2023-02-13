NAME = webserv
SRCS =	src/main.cpp \
		src/ISocket.class.cpp \
		src/BindSocket.class.cpp \
		src/ClientSocket.class.cpp \
		src/ListenSocket.class.cpp


OBJS = $(SRCS:%.cpp=%.o)
CC = c++
RM = rm -f
INCDIR = inc
FLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -I$(INCDIR)

R = \033[38;5;1m
G = \033[38;5;2m
B = \033[38;5;4m
D = \033[38;5;255m

.cpp.o:
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(B)Building $(NAME) program.$(D)"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(G)$(NAME) program created.$(D)"

clean:
	@echo "$(R)Remove all object files.$(D)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(R)Remove $(NAME) program if present.$(D)"
	$(RM) $(NAME)

re: fclean all

.PHONY:  all clean fclean re
