# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eterman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/22 12:15:47 by eterman           #+#    #+#              #
#    Updated: 2016/10/22 15:33:03 by eterman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -r - recursive.
# I'm sure there's a better way, but still... this is a working one.
#
# The following Makefile will recompile only the modified files from src
#
# Use make -s (quiet mode).
# If you want to compile without flags, change $(COMPILE):
#	$(CC) $(INCLUDES) $(FLAGS).
#
# How it works ?
#	1) SRC finds all c files in 'src' (with full path).
#	2) SRC_FILES finds the name of each c file (without path).
#	3) INCLUDES includes all headers form all directories form the current.
#	4) Creates a rule for each '.o' file (here's the trick with compile
#		the modified only).

GREEN 		=	'\033[0;32m'
RED			=	'\033[0;31m'
CYAN 		=	'\033[0;36m'
MAGENTA		=	'\033[35m'
YELLOW		=	'\033[33m'
EOC			=	'\033[0m'


NAME		=	libft.a
FLAGS		=	-Wall -Wextra -Werror
CC			=	gcc

ASCII_NAME	=   " \
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n	\
░███░░░░░░░░░░███░█████████░░░████████████░░░░░░░░░░░░░\n	\
░███░░░░░░░░░░░░░░███░░░░░███░███░░░░░░░░░░░░░░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░░░░░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░█████████████████████\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░█████████░░░████████████░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░███░░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░███░░░░░░░░░░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░████████████░███░███░░░░░███░███░░░░░░░░░░███░░░░░░░░░\n	\
░████████████░███░█████████░░░███░░░░░░░░░░███░░░░░░░░░\n	\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"

LIB_ROOT	=	..

LIBS		=								\
				$(LIB_ROOT)/listlib/listlib.a		\
				$(LIB_ROOT)/eventlib/eventlib.a		\
				$(LIB_ROOT)/unittestlib/utestlib.a	\
				$(LIB_ROOT)/hashtablib/hashtablib.a	\
				-ltermcap

INC_DIRS	=	$(shell find includes -type d)
INC_PROJ	=	$(foreach d, $(INC_DIRS), -I $d)

INCLUDES	=	$(INC_PROJ)					\
				-I $(LIB_ROOT)/listlib/includes		\
				-I $(LIB_ROOT)/unittestlib/includes	\
				-I $(LIB_ROOT)/hashtablib/includes	\
				-I $(LIB_ROOT)/eventlib/includes

# Compile can include flags or other stuff, so it can be useful when I
# want to compile without flags

COMPILE		=	$(CC) $(INCLUDES) $(FLAGS)

# Finds all '.c' files in 'src'

SRC			=	$(shell find src -name '*.c')

# This will contain an array of all SRC files without path.
# Ex: src/dir1/file.c --> file.c
# This functionality is used for OBJS

SRC_FILES	=	$(notdir $(SRC))

OBJDIR		=	objs
OBJS_NAMES	=	$(SRC_FILES:.c=.o)
OBJS		=	$(addprefix $(OBJDIR)/,$(OBJS_NAMES))

all: $(NAME)

# Quietly creates an $(OBJDIR) directory

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Like this, I can make multiple directories in src.
# If it doesn't match the first, it goes to the second, etc ...
# Let's say I'm looking for f1.o and f1.c is located as src/dir0/f1.c:
#	First it will search if there's any match in src -- it won't match.
#	Then it will try to find it in any
#	subdirectory of src, and it's gonna find it.

define COMPILE_FILE
	@$(COMPILE) -c $(1) -o $(2)
	@(if [ $$? -eq 0 ] ; \
		then echo $(GREEN)[OK]$(EOC) $(MAGENTA)$(1)$(EOC) ; fi)
endef

$(OBJDIR)/%.o: src/%.c
	$(call COMPILE_FILE,$<,$@)

$(OBJDIR)/%.o: src/*/%.c
	$(call COMPILE_FILE,$<,$@)

$(OBJDIR)/%.o: src/*/*/%.c
	$(call COMPILE_FILE,$<,$@)

$(OBJDIR)/%.o: src/*/*/*/%.c
	$(call COMPILE_FILE,$<,$@)

$(OBJDIR)/%.o: src/*/*/*/*/%.c
	$(call COMPILE_FILE,$<,$@)

$(OBJDIR)/%.o: src/*/*/*/*/*/%.c
	$(call COMPILE_FILE,$<,$@)

$(OBJDIR)/%.o: src/*/*/*/*/*/%.c
	$(call COMPILE_FILE,$<,$@)

# The main rule
# First, it makes sure that $(OBJDIR) exists.
# I pass as prerequisites all OBJS (and right above, I wrote a rule for each
#	'.o' file).


$(NAME): $(OBJDIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@printf $(ASCII_NAME)
	@echo -n $(YELLOW) ""
	ranlib $(NAME)
	@echo -n $(EOC) ""

clean:
	@echo "rm -f objs"
	@rm -f $(OBJS)
	@echo "rm -rf " $(OBJDIR)
	@rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
