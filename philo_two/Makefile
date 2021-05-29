NAME = philo_two
CFLAGS = -Wall -Wextra -Werror
CC = gcc

SRC = 	checker.c		\
		main.c			\
		message.c		\
		outils.c		\
		parsing.c

OBJ = $(SRC:.c=.o)

bold = $(shell tput bold)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -lncurses -o $(NAME)
	@echo "${bold}DONE!"

%.o : %.c
	@echo "${bold}COMPILING ..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "${bold}LIBRARY SUCCESSFULLY REMOVED"

fclean: clean
	@rm -f $(NAME)
	@echo "${bold}EXECUTION FILES SUCCESSFULLY REMOVED"

re: fclean all