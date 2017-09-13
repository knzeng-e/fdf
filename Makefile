NAME = fdf
SRC_PATH = ./srcs/
SRC_NAME = $(shell ls $(SRC_PATH) | grep .c)
INC_PATH = ./includes/
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_PATH = ./libft/srcs/
LIB_SRCS = $(shell ls $(LIB_PATH) | grep .c)
LIB_INC = /libft/includes/
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
CC = gcc
CFLAGS = -Wall -Werror -Wextra
FFLAGS = -framework AppKit -framework OpenGL -Lmlx -L. -Llibft -lmlx -lft

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(FFLAGS) $(OBJ) -I$(LIB_INC) -I$(INC_PATH) -Imlx -o $@

lib :
	clear
	@echo "\033[31m >>> \033[32mCOMPILING \"$(NAME)\"..\033[31m <<<\033[0m"
	@make -C libft/ fclean && make -C libft/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo '' > /dev/null
	@$(CC) $(CFLAGS) -c $< -I libft/includes -I ./includes -I mlx -o $@

clean:
	@echo "Remove all .o files"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo '' > /dev/null

fclean: clean
		@rm -f $(NAME)
		@echo "\033[31m--- \033[33;4m \"$(NAME)\" EXECUTABLE DELETED\033[0m"

norme :
	norminette $(INC_PATH) $(SRC_PATH)

re: fclean all

.PHONY : all clean fclean norme re
