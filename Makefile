NAME	= minishell

FT_DIR	= libft-improved
RL_DIR	= readline
SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= inc

RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS	= -Llibft-improved
LDLIBS	= -lft -lreadline

FILES	= $(basename $(notdir $(wildcard src/*.c)))
SRC		= $(addsuffix .c,$(addprefix $(SRC_DIR)/,$(FILES)))
OBJ		= $(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(FILES)))

.PHONY : all re clean fclean ft
.SILENT :

all : ft $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ) : $(SRC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(SRC) $(CFLAGS) -c -o $(OBJ)

ft :
	$(MAKE) -C $(FT_DIR)

re : fclean all

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(FT_DIR) fclean
