
SRCS =	./srcs/main.c ./srcs/start_pipex.c ./srcs/config.c ./srcs/error.c \
		./srcs/utils/ft_calloc.c ./srcs/utils/ft_split.c ./srcs/utils/ft_bzero.c ./srcs/utils/ft_strlen.c \
		./srcs/utils/ft_substr.c ./srcs/utils/ft_strjoin.c

OBJS = $(SRCS:.c=.o)

NAME = pipex

CFLAGS = -g 

CC = gcc

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME) filein 'cat' 'wc' fileout

.PHONY: fclean re clean all run