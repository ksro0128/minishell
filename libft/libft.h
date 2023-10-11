/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:29:53 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/19 16:01:58 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define SSIZE_SIZE 9223372036854775807

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_buf
{
	char			*buf;
	size_t			b_len;
	struct s_buf	*next;
}	t_buf;

typedef struct s_gnl
{
	int				fd;
	int				flag;
	void			*content;
	char			*buf;
	size_t			buf_len;
	struct s_gnl	*next;
}	t_gnl;

typedef struct s_list
{
	int				num;
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;	
}	t_list;

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}	t_btree;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_putnbr_fd(int n, int fd);
int		ft_putendl_fd(char *s, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
int		ft_putchar_fd(char c, int fd);
char	*ft_itoa(int n);
int		ft_abs(int a);

// linked_list
void	lstadd_front(t_list **lst, t_list *new);
void	lstadd_back(t_list **lst, t_list *new);
void	lstiter(t_list *lst, void (*f)(void *));
void	lstclear(t_list **lst, void (*del)(void *));
void	lstdelone(t_list *lst, void (*del)(void *));
t_list	*lstlast(t_list *lst);
int		lstsize(t_list *lst);
t_list	*lstnew(void *content);
t_list	*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// circular_list
t_list	*cll_new(int num);
int		clladd_prev(t_list **head, int num);
int		clladd_next(t_list **head, int num);
int		clladd(t_list **head, int num);
int		cllpush_next(t_list **head, t_list *new_node);
int		cllpush(t_list	**head, t_list *new_node);
t_list	*cllpop_next(t_list **head);
t_list	*cllpop(t_list **head);
void	cllswap_next(t_list *node);
void	cll_print(t_list *node, int size);
void	cll_print_rev(t_list *node, int size);
void	cll_delone(t_list **head);

// btree
t_btree	*bt_create_node(void *item);
void	bt_apply_prefix(t_btree *root, void (*applyf)(void *));
void	bt_apply_infix(t_btree *root, void (*applyf)(void *));
void	bt_apply_suffix(t_btree *root, void (*applyf)(void *));
void	bt_insert_data(t_btree **root, void *item, int (*cmpf)(void*, void*));
void	*bt_search_item(t_btree *root, void *data_ref, \
						int (*cmpf)(void *, void *));
int		bt_level_count(t_btree *root);

// get_next_line
char	*ft_make_alloc(size_t len, char *src, size_t st_idx, int flag);
char	*ft_strdup2(t_gnl *node, char *buf, size_t len, int flag);
int		ft_strjoin_gnl(t_gnl *node, char const *s2, ssize_t read_tmp);
t_gnl	*ft_modify_fd(t_gnl **lst, t_gnl *new, int fd);
char	*ft_loop_read(t_gnl *tmp, char *buf, size_t idx);
char	*ft_make_line(t_gnl *tmp);
void	ft_free_node(t_gnl **head, int fd);
char	*get_next_line(int fd);

// ft_printf
int		ft_putunbr_fd(unsigned int n, int fd);
void	ft_puthexa_fd(unsigned int num, int *val, int flag, int fd);
void	ft_putaddr_fd(unsigned long long int num, int *val, int len, int fd);
int		ft_check_print(int fd, const char *s, va_list *ap);
int		ft_printf(const char *s, ...);
int		ft_fprintf(int fd, const char *s, ...);

#endif