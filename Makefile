# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/26 18:33:52 by oozkaya           #+#    #+#              #
#    Updated: 2019/03/20 14:26:41 by oozkaya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary
NAME = lem-in

# Compiler
CC = gcc

# Directories
SRC_PATH = src/
OBJ_PATH = obj/
LIB_PATH = libft
INC_PATH = includes/ \
		   $(LIB_PATH)/includes/ \

# Includes & libraries
CPPFLAGS = $(addprefix -I,$(INC_PATH))
LDFLAGS = -L $(LIB_PATH) $(SDL2_LIBS)
LDLIBS = -lft

# Sources
SRC_NAME =	\
			main.c\
			buffer.c\
			map_init.c\
			map_free.c\
			parser.c\
			parser_tools.c\
			parser_tools2.c\
			solver.c\
			valid_paths.c\
			sort_paths.c\
			print_solution.c\
			move_all.c\
			graph.c\
			bonus.c\
			map_info.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags with OS Compatibiliy
OS = $(shell uname)
ifeq ($(OS), Darwin)
	FLAGS_DEFAULT = -Werror -Wall -Wextra
endif
ifeq ($(OS), Linux)
	FLAGS_DEFAULT = -Wno-unused-result
endif
ifdef FLAGS
	ifeq ($(FLAGS), no)
		CFLAGS := $(ADDFLAGS)
	endif
	ifeq ($(FLAGS), debug)
		CFLAGS := $(FLAGS_DEFAULT) -ansi -pedantic -g $(ADDFLAGS)
	endif
else
	CFLAGS := $(FLAGS_DEFAULT) $(ADDFLAGS)
endif

# MAKEFLAGS
MAKEFLAGS += --no-print-directory

# Variables
COUNTER=0

# **************************************************************************** #
# SPECIALS CHARS                                                               #
# **************************************************************************** #
LOG_CLEAR = \033[2K
LOG_UP = \033[A
LOG_NOCOLOR = \033[0m
LOG_BOLD = \033[1m
LOG_UNDERLINE = \033[4m
LOG_BLINKING = \033[5m
LOG_BLACK = \033[1;30m
LOG_RED = \033[1;31m
LOG_GREEN = \033[1;32m
LOG_YELLOW = \033[1;33m
LOG_BLUE = \033[1;34m
LOG_VIOLET = \033[1;35m
LOG_CYAN = \033[1;36m
LOG_WHITE = \033[1;37m

TITLE = $(LOG_CLEAR)$(LOG_BLUE)
END_TITLE = $(LOG_NOCOLOR)
LINKING = "--$(LOG_CLEAR)$(LOG_GREEN)✓$(LOG_NOCOLOR)\tlinking " \
				".................. $(LOG_VIOLET)$<$(LOG_NOCOLOR)"
ASSEMBLING = "--$(LOG_CLEAR)$(LOG_GREEN)✓$(LOG_NOCOLOR)\tassembling " \
			 	"............... $(LOG_YELLOW)$(NAME)$(LOG_NOCOLOR)"
OBJECTS_DEL = "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion " \
				"............ $(LOG_RED)×$(LOG_NOCOLOR)"
BIN_DEL = "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion " \
				"............. $(LOG_RED)×$(LOG_NOCOLOR)"

# **************************************************************************** #
# RULES                                                                        #
# **************************************************************************** #
.PHONY: all, clean, fclean, re, norme

all: libft.a $(NAME)

$(NAME): setup_graphviz $(OBJ_PATH) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@if [ $(COUNTER) -ne 0 ]; then echo -e $(ASSEMBLING); fi;

libft.a:
	@make -C $(LIB_PATH)

setup_graphviz:
	@if [ $(OS) = Darwin ]; then make graphviz_Darwin; fi;
	@if [ $(OS) = Linux ]; then make graphviz_Linux; fi;

graphviz_Darwin:
	@if !(brew ls --versions graphviz > /dev/null); then \
		echo -e "$(TITLE)setup grapĥviz$(END_TITLE)"; \
		brew update && brew install graphviz; \
	fi;

graphviz_Linux:
	@if !(dot -V 2>/dev/null); then \
		echo -e "$(TITLE)setup graphviz$(END_TITLE)"; \
		sudo apt-get update -y; \
		sudo apt-get install -y graphviz; \
	fi;

$(OBJ_PATH):
	@echo -e "$(TITLE)build $(NAME)$(END_TITLE)"
	@echo -e "--$(LOG_CLEAR)Flags : $(CFLAGS)"
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo -e $(LINKING)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))

clean:
	@echo -e "$(TITLE)clean $(NAME)$(END_TITLE)"
	@echo -e $(OBJECTS_DEL)
	@rm -Rf $(OBJ_PATH)
	@make -C $(LIB_PATH) clean_quiet

fclean:
	@echo -e "$(TITLE)fclean $(NAME)$(END_TITLE)"
	@echo -e $(OBJECTS_DEL)
	@rm -Rf $(OBJ_PATH)
	@echo -e $(BIN_DEL)
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean_quiet

re: fclean all

norme:
	norminette $(SRC)
	norminette $(addprefix $(INC_PATH), *.h)

# **************************************************************************** #
# Personal notes :                                                             #
#                                                                              #
# $@ : rule's name                                                             #
# $^ : all dependencies after ':'                                              #
# $< : corresponding dependency                                                #
# || : of there is an error, execute the command after the double pipe         #
#                                                                              #
# **************************************************************************** #
