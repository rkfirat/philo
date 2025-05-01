NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread -pthread

SRCS = check_args_bonus.c  init_data_bonus.c  philo_bonus.c  routine_bonus.c  utils_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

main:
	make re
	make clean
	clear

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re