NAME	= minishell

FT_DIR	= libft-improved
RL_DIR	= readline
SRC_DIR	= src
OBJ_DIR	= obj

CFLAGS		= -Wall -Wextra -Werror
LIBFT_FLAGS	= -lft -L$(FT_DIR)
RL_FLAGS	= -lreadline -L$(RL_DIR)

FILES	= $(basename $(notdir $(wildcard src/*.c)))
SRC		= $(addsuffix .c,$(addprefix $(SRC_DIR),$(FILES)))
OBJ		= $(addsuffix .o,$(addprefix $(OBJ_DIR),$(FILES)))

.PHONY : all re clean fclean

all : $(NAME)

$(NAME) : $(OBJ_DIR)
	$(MAKE) -C $(FT_DIR)
	cc $(LIBFT_FLAGS) $(RL_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c #minishell.h
	cc 

