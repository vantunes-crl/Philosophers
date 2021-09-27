NAME = philo

FLAGS = -Wall -Werror -Wextra -lpthread

SRCS = actions.c init.c philo.c utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	gcc $(OBJS) $(FLAGS) -o $(NAME)

all: $(NAME) clean

clean:
	rm $(OBJS)

re:	clean all

fclean:
	rm $(NAME) $(OBJS)