SRCS_C = client.c \
		tools.c

SRCS_S = server.c \
		puts.c


CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME_C = client
NAME_S = server

OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.c=.o)

%.o : %.c minitalk.h
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME_C) $(NAME_S)

$(NAME_C) : $(OBJS_C)
	$(CC) $(FLAGS) $(OBJS_C) -o $(NAME_C)

$(NAME_S) : $(OBJS_S)
	$(CC) $(FLAGS) $(OBJS_S) -o $(NAME_S)

clean :
	/bin/rm -f $(OBJS_C)
	/bin/rm -f $(OBJS_S)

fclean : clean
	/bin/rm -f $(NAME_C)
	/bin/rm -f $(NAME_S)

re : fclean all
