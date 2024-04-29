# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/28 00:26:32 by pepaloma          #+#    #+#              #
#    Updated: 2024/04/28 14:01:30 by pepaloma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

FT_DIR	= libft-improved
RL_DIR	= readline
SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= inc

RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -I$(HOME)/.brew/Cellar/readline/8.2.10/include -g
LDFLAGS	= -Llibft-improved -L$(HOME)/.brew/Cellar/readline/8.2.10/lib
LDLIBS	= -lft -lreadline

FILES	= builtins clear_commands exec_commands expand_parameters ft_cd \
			ft_echo ft_env ft_exit ft_export ft_pwd ft_unset here_doc \
			init_commands minishell parse_line redirect_io utils_env_b \
			utils_env utils
SRC		= $(addsuffix .c,$(addprefix $(SRC_DIR)/,$(FILES)))
OBJ		= $(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(FILES)))

.PHONY : all re clean fclean ft
#.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C $(FT_DIR)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	if ! [ -f ${HOME}/.inputrc ]; then \
	echo "set echo-control-characters Off" > ${HOME}/.inputrc; fi

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

re : fclean all

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(FT_DIR) fclean
