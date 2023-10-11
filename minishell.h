/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:17:05 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/11 13:48:37 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>

# define INT_MAX   2147483647
# define INT_MIN  -2147483648

# define TRUE       1
# define FALSE      0
# define SUCCESS    0
# define FAIL       1
# define ERROR      1
# define FD_ERROR  -1
# define NULLCMD   -2
# define NOT_BLTIN -1

# define FD_RD     0
# define FD_WR     1

// error state
# define E_OTHER  0
# define E_SYNTAX 1
# define E_OPEN   2
# define E_ENVSET 3
# define E_TWOARG 4
# define E_NAN    5
# define E_TOMANY 6
# define E_TOFEW  7
# define E_CMDNF  8
# define E_AMBIG  9
# define E_NVALID 10 
# define E_QUOTE  11

// builtin state
# define B_CD 0
# define B_ECHO 1
# define B_ENV 2
# define B_EXIT 3
# define B_PWD 4
# define B_UNSET 5
# define B_EXPORT 6

// signal stat
# define SIG_HERE 1
# define SIG_CMD  2

// state
# define S_UNDEF -1
# define S_STAT  1
# define S_META  2
# define S_FINAL 3

# define S_META_CHAR 10
# define S_CMD 11
# define S_SUB_CMD 12
# define S_QUOTE 13

// meta character
# define M_SPACE 20
# define M_TAB   21
# define M_PIPE  22
# define M_R_SSHIFT 23
# define M_L_SSHIFT 24
# define M_R_DSHIFT 25
# define M_L_DSHIFT 26
# define M_OTHER    27

# define F_FILE      30
# define F_CMD       31
# define F_WORD      32
# define F_AMBERR    33
# define F_HEREDOC   34
# define F_PIPE      22
# define F_REDIR_IN  23
# define F_REDIR_OUT 24
# define F_REDIR_APP 26

// character
# define C_DOUBLE_QUOTE '\"'
# define C_SINGLE_QUOTE '\''
# define C_BACK_SLASH '\\'
# define C_META_CHAR " \t\n|&;()<>"
# define C_WSPACE " \t"
# define C_SPACE ' '
# define C_TAB '\t'
# define C_PIPE '|'
# define C_R_SHIFT '<'
# define C_L_SHIFT '>'

int	g_c_signal;

typedef struct s_token
{
	int				stat;
	char			*str;
	int				str_len;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_env_tmp
{
	int					stat;
	char				*str;
	struct s_env_tmp	*next;
}	t_env_tmp;

typedef struct s_exec_mat
{
	t_token			*token_list;
	char			*cmd;
	char			**arg;
	int				pid;
	int				fd_in;
	int				fd_out;
	struct s_msh	*msh;
}	t_exec_mat;

typedef struct s_msh
{
	struct termios		old_set;
	struct termios		new_set;
	t_env				*env_list;
	t_token				*token_list;
	struct sigaction	sigact;
	t_token				**token_list_array;
	t_exec_mat			*ex_mat;
	char				**path;
	int					pipe_fd[2];
	int					exit_code;
	int					pipe_cnt;
	int					stat;
	int					tmp_fd;
}t_msh;

// libft
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memset(void *b, int c, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isdigit(int c);
char		*ft_itoa(int n);
int			ft_fprintf(int fd, const char *s, ...);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
char		**ft_split(char *s, char c);
int			ft_putendl_fd(char *s, int fd);

// builtins
int			ft_env(char **env);
int			ft_exit(t_msh *msh, char **arg);
int			ft_unset(t_msh *msh, char **arg, t_env *env_list);
int			ft_pwd(void);
int			ft_echo(t_msh *msh, char **arg);
int			ft_cd(t_msh *msh, char **arg, t_env *env);
int			ft_export(t_msh *msh, char **arg, t_env *env_list);
int			check_key(char *str);
t_env		*copy_env(t_env *env_list);
void		swap_env(t_env *token);
int			get_env_list_size(t_env *env_list);
void		print_export(t_env *env_list);
void		free_copy_env_list(t_env *env_list);
void		sorting_env(t_env *env_list);
char		*get_key_str(char *str);
int			check_key(char *str);
char		*get_value_str(char *str);
int			is_cmd_a_builtin(char *cmd);
int			exec_builtin(t_msh *msh, t_exec_mat *mat, char **env, int i);

// parse utils
char		*read_cmdline(t_msh *msh);
int			check_valid_quotes(char *cmd);
void		separate_by_quotes(t_token **token_list, char *cmd);
void		separate_by_meta_char(t_token **p_token_list, char *sepstr);
void		merge_except_meta_char(t_token **p_token_list);
char		*merge_two_quote_token(t_token *token_list, \
			char *p_str, t_token *prev);
int			check_syntex_error(t_msh *msh, t_token *token_list, \
			int prev_meta_flag);
int			set_heredoc_and_tmp_file(t_token *p_token_list, t_msh *msh);
void		remove_white_space_token(t_token **token_list);
void		set_status(char c, t_token *tmp, char *str);
void		set_meta_char(t_token *head, char *str, int idx);
void		redefine_status_of_token(t_token *token_list);

// parse utils utils
char		*make_tmp_file(void);
char		*apply_env_str(char *str, t_msh *msh);
void		make_heredoc_applied_env(int fd, char *tmp_file, \
			char *limiter, t_msh *msh);
void		make_heredoc_not_applied_env(int fd, char *tmp_file, char *limiter);
char		*merge_token_to_str(t_env_tmp *head);
char		*make_heredoc(char *limiter, t_msh *msh);
int			check_limiter(char *limiter);
char		*remove_quotes_str(char *str);

// handling error
int			handling_error(t_msh *msh, int errnum, \
			char *fst_str, char *snd_str);

// minishell_utils
int			is_white_space(int stat);
int			is_meta_char(char c, char *sepstr);
char		*ft_strjoin_1free(char *s1, char *s2);
char		*ft_strjoin_2free(char *s1, char *s2);
char		*ft_strjoin_12free(char *s1, char *s2);

// env_utils
t_env_tmp	*create_env_tmp(char *str, int stat);
void		free_env_tmp(t_env_tmp *head);
void		apply_env_token(t_env_tmp *token, t_msh *msh);
void		devided_by_white_space(t_env_tmp *token);

// minishell_env
t_env		*get_env(char *env[]);
void		print_env(t_env *head);
char		**make_t_env_to_envp(t_env *env);
char		*find_env_value(t_env *head, char *key);
int			apply_env_to_one_token(t_token *token, t_msh *msh);
t_env		*find_env(t_env *head, char *key);
void		delete_key_env(t_env *head, char *key);
t_env		*create_env_token(char *key, char *value);
char		*cut_s_to_i(char *str, int s, int i);
t_env_tmp	*make_tmp_list_devided_by_quotes(char *str);
void		apply_merge_dollar_quotes(t_env_tmp *head);
char		*extract_env(char *str, int *i, t_msh *msh);
int			change_or_add_env(t_env *env_list, char *str);
void		applying_env(t_msh *msh, t_exec_mat *cur_mat);
int			t_env_len(t_env *env);

// minishell_token_utils
void		set_token(t_token *token, int stat, char *str);
t_token		*create_token(char *str, int stat);
void		add_token(t_token *head, char *str, int idx, int stat);
void		delete_all_token(t_token **head);
void		print_token(t_token *head);
void		print_strs(char **strs);

void		change_to_removed_quotes(t_token *token_list);
void		make_list_array(t_msh *msh);

// minishell_signal
void		signal_ignore_parent(int flag);
void		signal_setting_child(int flag);
void		signal_initial_parent(void);
void		termios_initial_parent(t_msh *msh);
void		set_signal_terminal_init(t_msh *msh);
void		set_termios(t_msh *msh);
void		unset_termios(t_msh *msh);

// minishell_pipe
void		processing_each_cmd(t_msh *msh);
char		**parsing_path_env(t_msh *msh);
int			find_in_out_file(t_msh *msh, t_exec_mat *cur_mat, int i);
int			ft_modi_child_fd(t_msh *msh, t_exec_mat *cur_mat, int i);

// minishell_free
void		free_all_the_stuffs(t_msh *msh);
void		free_strs(char **strs);

void		pass_until_char(char *str, int *i, char c);
char		*extract_env_dq(char *str, int *i);
t_env_tmp	*create_quotes_token(char *str, int *i);
int			apply_env_tmp_to_token(t_token *token, t_env_tmp *head);
void		insert_env_tmp(t_env_tmp *cur, char *str, int stat);
void		remove_ws_env_tmp(t_env_tmp *head);
void		apply_merge_env_tmp(t_env_tmp *head);
void		insert_token(t_token *cur, char *str, int stat);
void		apply_env_tmp(t_env_tmp *head, t_msh *msh);
void		apply_devide_by_white_space(t_env_tmp *head);
char		*extract_env_var(char *str, int *i, t_env *env_list);
char		*getstr_until_white_space(char *str, int *i);
char		**make_t_env_to_envp(t_env *env);
void		print_env(t_env *head);
char		*find_env_value(t_env *head, char *key);
void		delete_key_env(t_env *head, char *key);
#endif