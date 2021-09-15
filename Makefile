NAME = philo

FLAGS = -Wall -Werror -Wextra

SRCS = actions.c init.c philo.c utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

all: $(NAME) clean

clean:
	rm $(OBJS)

fclean:
	rm $(NAME) $(OBJS)