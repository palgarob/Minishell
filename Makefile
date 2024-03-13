NAME	= minishell

FT_DIR	= libft-improved
RL_DIR	= readline
SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= inc

FT_LINKER	= -L$(FT_DIR)
RL_LINKER	= -L$(RL_DIR)
FT_LIB		= -lft
RL_LIB		= -lreadline

RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS	= $(FT_LINKER) $(RL_LINKER)
LDLIBS	= $(FT_LIB) $(RL_LIB)

FILES	= $(basename $(notdir $(wildcard src/*.c)))
SRC		= $(addsuffix .c,$(addprefix $(SRC_DIR)/,$(FILES)))
OBJ		= $(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(FILES)))

.PHONY : all re clean fclean

all : $(NAME)
	@$(MAKE) -C $(FT_DIR)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ) : $(SRC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(SRC) $(CFLAGS) -c -o $(OBJ)

re : fclean all

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJ_DIR)
