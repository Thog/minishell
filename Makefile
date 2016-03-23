# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/04 11:53:01 by tguillem          #+#    #+#              #
#    Updated: 2016/03/23 15:47:04 by tguillem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -g -Wall -Wextra -Werror -I./includes
PRGFLAGS = -lft
CC = gcc

NAME = minishell
LIB = libft
SRC = main.c init.c loop.c array_utils.c executor.c buildin.c error.c \
	  array_converter.c buildin_env.c buildin_cd.c utils.c env_utils.c
SRCDIR = src
OUTDIR = out
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OUTDIR)/, $(SRC:.c=.o))
all: $(NAME)

$(NAME): $(OUTDIR) $(OBJ)
	(cd $(LIB) && $(MAKE))
	$(CC) -o $(NAME) $(CFLAGS) -I./libft -L./libft $(OBJ) $(PRGFLAGS)
$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I $(LIB) -o $@ -c $? $(CFLAGS)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

clean:
	@(cd $(LIB) && $(MAKE) $@)
	@rm -f $(OBJ)
	@rm -rf $(OUTDIR)

fclean: clean
	@(cd $(LIB) && $(MAKE) $@)
	@rm -f $(NAME)

.PHONY: clean fclean re

re: fclean all
