# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 16:51:36 by gchernys          #+#    #+#              #
#    Updated: 2023/03/04 01:11:43 by gchernys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

AR = ar rcs

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=address 

LIBFT = cd libft && make

FILES =	./main.c						\
		./src/philosopher_atoi.c		\
		./src/initialize_everything.c	\
		./src/philosopher_actions.c		\
		./src/philosopher_utils.c		\
		./src/philosopher_launcher.c
		
FILES_O = $(FILES:.c=.o)


all: $(NAME)

$(NAME) :	$(FILES_O)
	      	$(CC) $(CFLAGS) $(FILES_O) -o philo

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf *.o
	cd src && rm -rf *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re