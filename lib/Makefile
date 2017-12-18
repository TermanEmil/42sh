# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eterman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/22 12:15:47 by eterman           #+#    #+#              #
#    Updated: 2016/12/27 20:02:30 by eterman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -r - recursive.
# I'm sure there's a better way, but still... this is a working one.
#
# The following Makefile will recompile only the modified files from src and
# includes all headers -r from includes (and for my case, libft/includes -r)
#
# Use make -s (quiet mode).
# If you want to compile without flags, change $(COMPILE):
#	$(CC) $(INCLUDES) $(FLAGS).
#
# How it works ?
#	1) SRC finds all c files in 'src' (with full path).
#	2) SRC_FILES finds the name of each c file (without path).
#	3) INCLUDES includes all headers form all directories form the current
#		project includes and libft's includes.
#	4) Creates a rule for each '.o' file (here's the trick with compile
#		the modified only).

NAME		=	libs
FLAGS		=	-Wall -Wextra -Werror
CC			=	gcc


LIBROOT		=	.
LIB_DIRS	=								\
				$(LIBROOT)/listlib			\
				$(LIBROOT)/libft			\
				$(LIBROOT)/eventlib			\
				$(LIBROOT)/hashtablib		\
				$(LIBROOT)/termlib			\
				$(LIBROOT)/unittestlib		\

$(NAME):
	$(foreach d, $(LIB_DIRS), make -C $d;)

clean:
	$(foreach d, $(LIB_DIRS), make clean -C $d;)

fclean:
	$(foreach d, $(LIB_DIRS), make fclean -C $d;)

re:
	$(foreach d, $(LIB_DIRS), make re -C $d;)