NAME_SRV        =		server

NAME_CLI        =		client

CC              =       cc

FLAG            =       -Wall -Wextra -Werror -g

LIBFT_FILE      =		libft.a

LIBFT_PATH      =       ./libft/

LIBFT_LIB       =       $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

LIBFT_EX        =       $(LIBFT_LIB) $(FLAG)

C_SRV_FILE      =       server.c	\

C_CLI_FILE      =       client.c	\

SRC_DIR         =       ./src/

INC_DIR         =       ./includes/

SRC_SRV			=		$(addprefix $(SRC_DIR),$(C_SRV_FILE))
SRC_CLI			=		$(addprefix $(SRC_DIR),$(C_CLI_FILE))

OBJ_SRV			=		$(SRC_SRV:.c=.o)

OBJ_CLI			=		$(SRC_CLI:.c=.o)

.c.o:
		$(CC) $(FLAG) -c $< -o $@

all: $(NAME_SRV) $(NAME_CLI)

./libft/libft.a:
		@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)...\n"
		@make -sC $(LIBFT_PATH)
		@echo "\033[1;32mLIBFT created\033[0m\n"

$(NAME_SRV): ./libft/libft.a $(OBJ_SRV)
		@echo "\033[0;33m\nCOMPILING SERVER...\n"
		$(CC) $(OBJ_SRV) $(LIBFT_EX) -o $(NAME_SRV)
		@echo "\033[1;32m./server created\033[0m\n"

$(NAME_CLI): ./libft/libft.a $(OBJ_CLI)
		@echo "\033[0;33m\nCOMPILING CLIENT...\n"
		$(CC) $(OBJ_CLI) $(LIBFT_EX) -o $(NAME_CLI)
		@echo "\033[1;32m./client created\033[0m\n"

clean:
		@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
		@make clean -sC $(LIBFT_PATH)
		@echo "\033[1;32mDone\n"
		@echo "\033[0;31mDeleting all object...\n"
		@rm -f $(OBJ_SRV) $(OBJ_CLI) $(NAME_SRV) $(NAME_CLI)
		@echo "\033[1;32mDone\033[0m\n"

fclean: clean
		@echo "\033[0;31mDeleting executable..."
		@rm -f $(NAME_SRV) $(NAME_CLI)
		@make clean -sC $(LIBFT_PATH)
		@echo "\033[1;32mDone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
