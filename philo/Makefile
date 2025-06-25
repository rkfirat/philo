NAME = philo
CFLAGS = -Wall -Wextra -Werror -g -pthread

SRCS = check_args.c  init_data.c  philo.c  routine.c  utils.c monitor.c

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
