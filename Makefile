CC = cc
CFLAGS = -Werror -Wall -Wextra
PARSE = /separate_by_quotes.c /separate_by_meta_char.c    /merge_except_meta_char.c \
		/check_syntex_error.c /set_heredoc_and_tmp_file.c /remove_white_space_token.c \
		/meta_char_function.c /redefine_status_of_token.c  /set_heredoc_and_tmp_file_utils.c \
		 /read_cmdline.c      /set_heredoc_and_tmp_file_utils2.c \

PARSE_DIR = parse_utils/

SIGNAL = /minishell_signal.c /minishell_signal2.c /minishell_signal3.c

SIGNAL_DIR = signal_utils/

PIPE = /minishell_pipe.c /minishell_pipe_child.c /minishell_file.c

PIPE_DIR  = pipe_utils/

BUILT_INS = /ft_cd.c /ft_echo.c /ft_env_exit.c /ft_pwd.c /ft_unset.c /ft_export.c \
			/ft_export_utils1.c /ft_export_utils2.c /check_builtins.c

BUILT_INS_DIR = builtins/

ENV =   /minishell_env.c /minishell_env_utils.c /minishell_apply_env.c /minishell_apply_env_utils1.c \
		/minishell_apply_env_utils2.c /minishell_apply_env_utils3.c /minishell_apply_env_utils4.c 

ENV_DIR = env_utils/

ERROR = /error_handling.c

ERROR_DIR = error_utils/

MAIN_SRCS = main.c minishell_utils.c minishell_token_utils.c minishell_make_list_array.c \
			minishell_free.c minishell_main_apply_env.c

SRCS = $(MAIN_SRCS) $(subst /,$(PARSE_DIR),$(PARSE)) $(subst /,$(BUILT_INS_DIR),$(BUILT_INS)) \
					$(subst /,$(ERROR_DIR),$(ERROR)) $(subst /,$(PIPE_DIR),$(PIPE)) \
					$(subst /,$(SIGNAL_DIR),$(SIGNAL)) $(subst /,$(ENV_DIR),$(ENV))
OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT = ./libft/libft.a

all :$(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(LIBFT_SRCS)
	$(CC) -lreadline -lcurses -o $(NAME) $(OBJS) $(LIBFT) -I./

%.o : %.c
	$(CC) -c $^ -o $@

$(LIBFT) :
	make -C ./libft/

clean :
	make -C ./libft/ clean
	rm -f $(OBJS)

fclean : clean
	make -C ./libft/ fclean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : re fclean clean all