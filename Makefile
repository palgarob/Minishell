NAME	= minishell

FT_DIR	= libft-improved
RL_DIR	= readline
SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= inc

RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -I$(HOME)/.brew/Cellar/readline/8.2.10/include
LDFLAGS	= -Llibft-improved -L$(HOME)/.brew/Cellar/readline/8.2.10/lib
LDLIBS	= -lft -lreadline

FILES	= $(basename $(notdir $(wildcard src/*.c)))
SRC		= $(addsuffix .c,$(addprefix $(SRC_DIR)/,$(FILES)))
OBJ		= $(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(FILES)))

.PHONY : all re clean fclean ft
.SILENT :

all : ft $(NAME)

$(NAME) : $(OBJ)
	$(CC) -fsanitize=address $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

ft :
	$(MAKE) -C $(FT_DIR)

re : fclean all

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(FT_DIR) fclean
