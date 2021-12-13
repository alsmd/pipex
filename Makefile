
SRCS =	./srcs/main.c ./srcs/start_pipex.c ./srcs/config.c ./srcs/error.c \
		./srcs/utils/ft_calloc.c ./srcs/utils/ft_split.c ./srcs/utils/ft_bzero.c ./srcs/utils/ft_strlen.c \
		./srcs/utils/ft_substr.c ./srcs/utils/ft_strjoin.c ./srcs/utils/ft_strncmp.c ./srcs/utils/get_next_line.c \
		./srcs/utils/handler_final_file.c

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
	valgrind ./$(NAME) here_doc ok 'cat' 'cat' fileout

.PHONY: fclean re clean all run