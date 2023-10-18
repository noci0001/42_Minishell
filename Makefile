NAME	= minishell

CC			= gcc
READLINE	= -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
CFLAGS		= -g -I headers/ -I libft/libft.a

RM			= rm -rf

LIBFT		= -L libft -lft

HEADER		= minshell.h

MAIN		= main main_program_functions main_program_functions2

PARSING		= parsing syntax_analysis tokenization tokenization2 expansion

UTILS		= is_type_utils utils utils2 utils3 utils4 free

EXECUTION	= execution redir redir2 command_execution command_execution2 command_execution3

BUILTINS	= builtins ft_cd ft_cd2 ft_echo ft_env ft_export ft_export2 ft_pwd ft_unset ft_unset2

SRC =		$(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
			$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
			$(addsuffix .c, $(addprefix src/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix src/execution/, $(EXECUTION))) \
			$(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS)))

OBJ			= $(SRC:c=o)

all:		$(NAME)

$(NAME):	$(OBJ)
	@make -sC libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE)

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@make clean -C libft/
	@rm -f obj/$(OBJ)

fclean:
	@make fclean -C libft/
	@rm -f obj/*.o
	@rm src/main/*.o src/builtins/*.o src/utils/*.o src/parsing/*.o src/execution/*.o
	@rm -f $(NAME)
	@rm -rf minishell.dSYM/
	@rm -rf minishell.dSYM
	@rm -rf minishell

re:		fclean all

norm:
	@mv src/main/main.o src/parsing/*.o src/builtins/*.o src/utils/*.o ./obj