SRC = main.cpp

OBJ = ${SRC:.cpp=.o}

NAME = BitcoinExchange

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

RM = rm -f

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		$(RM) -r $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
