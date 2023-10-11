CC = cc
CFLAGS = -Wall -Wextra -Werror
ORIGIN = ./origin/ft_atoi.c ./origin/ft_bzero.c ./origin/ft_calloc.c ./origin/ft_isalnum.c \
	./origin/ft_isalpha.c ./origin/ft_isascii.c ./origin/ft_isdigit.c ./origin/ft_isprint.c \
	./origin/ft_itoa.c ./origin/ft_memchr.c ./origin/ft_memcmp.c ./origin/ft_memcpy.c \
	./origin/ft_memmove.c ./origin/ft_memset.c ./origin/ft_putendl_fd.c ./origin/ft_split.c \
	./origin/ft_strchr.c ./origin/ft_strdup.c ./origin/ft_striteri.c ./origin/ft_strjoin.c \
	./origin/ft_strlcat.c ./origin/ft_strlcpy.c ./origin/ft_strlen.c ./origin/ft_strmapi.c \
	./origin/ft_strncmp.c ./origin/ft_strnstr.c ./origin/ft_strrchr.c ./origin/ft_strtrim.c \
	./origin/ft_substr.c ./origin/ft_tolower.c ./origin/ft_toupper.c ./origin/ft_abs.c
GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
PRINTF = ./ft_printf/ft_check_print.c ./ft_printf/ft_printf.c ./ft_printf/ft_putaddr_fd.c \
	./ft_printf/ft_putchar_fd.c ./ft_printf/ft_puthexa_fd.c ./ft_printf/ft_putnbr_fd.c \
	./ft_printf/ft_putstr_fd.c ./ft_printf/ft_putunbr_fd.c
LINKLST = ./linked_list/lstadd_back.c ./linked_list/lstadd_front.c ./linked_list/lstclear.c \
	./linked_list/lstdelone.c ./linked_list/lstiter.c ./linked_list/lstlast.c ./linked_list/lstmap.c \
	./linked_list/lstnew.c ./linked_list/lstsize.c
BTREE = ./btree/bt_apply_infix.c ./btree/bt_apply_prefix.c ./btree/bt_apply_suffix.c \
	./btree/bt_create_node.c ./btree/bt_insert_data.c ./btree/bt_level_count.c ./btree/bt_search_item.c
CLLST = ./cll/cll_delone.c ./cll/cll_new.c ./cll/clladd_prev.c ./cll/clladd_next.c ./cll/clladd.c \
	./cll/cllpush.c ./cll/cllpush_next.c ./cll/cllpop_next.c ./cll/cllpop.c \
	./cll/cllswap_next.c ./cll/cll_print.c ./cll/cll_print_rev.c
ORIGIN_OBJS = $(ORIGIN:.c=.o)
PRINTF_OBJS = $(PRINTF:.c=.o)
LINKLST_OBJS = $(LINKLST:.c=.o)
BTREE_OBJS = $(BTREE:.c=.o)
CLLST_OBJS = $(CLLST:.c=.o)
GNL_OBJS = $(GNL:.c=.o)
NAME = libft.a

ifdef BONUS_TRUE
SRCS = $(ORIGIN) $(PRINTF) $(LINKLST) $(BTREE) $(CLLST) $(GNL)
OBJS = $(ORIGIN_OBJS) $(PRINTF_OBJS) $(LINKLST_OBJS) $(BTREE_OBJS) $(CLLST_OBJS) $(GNL_OBJS)
else
SRCS = $(ORIGIN) $(PRINTF) $(LINKLST) $(BTREE) $(CLLST) $(GNL)
OBJS = $(ORIGIN_OBJS) $(PRINTF_OBJS) $(LINKLST_OBJS) $(BTREE_OBJS) $(CLLST_OBJS) $(GNL_OBJS)
endif

all : $(NAME)

bonus : $(OBJS)
	sleep 1
	make BONUS_TRUE=1 

$(NAME) : $(OBJS)
	ar -rcs $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	rm -rf $(ORIGIN_OBJS) $(PRINTF_OBJS) $(LINKLST_OBJS) $(BTREE_OBJS) $(CLLST_OBJS) $(GNL_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all