# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/01/07 10:54:13 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG	=	NO

NAME	=	libftprintf.a

SRCS	= 	ft_printf.c ft_printf_conversions.c ft_printf_itoas.c \
			ft_printf_handle.c ft_printf_utils.c

INCLUDES 	=	./

HEAD 		= $(INCLUDES)ft_printf.h

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS:.c=.o)

CC			= clang

CFLAGS		= -Wall -Wextra -Werror

LDFLAGS		= -L. -lftprintf

SANITIZE	= -g

VALGRIND	= valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --log-file=valgrind-out.txt ./a.out

## for libft compilation w/o chained list functions ##
LIBFT_DIR 	= libft/
LIBFT 		= $(LIBFT_DIR)libft.a
LIBFT_OBJ 	= $(LIBFT_DIR)*.o
LDFLAGSLIB	= -L$(LIBFT_DIR) -lft
####

all:	$(NAME)

$(LIBFT):
			@echo "\x1b[1m\x1b[31m--> Compiling Libft...\x1b[0m"
			@(cd $(LIBFT_DIR) && $(MAKE))

$(NAME):	$(OBJS) 
			@ar rcs $@ $^ $(LIBFT_OBJ)
			@ranlib $@
			@echo "\x1b[1m\x1b[31m-> $@ archived\x1b[0m"

exec :		a.out

ifeq ($(DEBUG),NO)
a.out :		$(NAME) main.c
			@$(CC) $(CFLAGS) main.c $(LDFLAGS) $(LDFLAGSLIB) -I$(LIBFT_DIR)
			@echo "\x1b[1m\x1b[32m-> main.c compiled\x1b[0m"
			@echo "\x1b[1m\x1b[31m\nTEST :\x1b[0m"
			@./a.out | cat -e
else
a.out :		$(NAME) main.c
			$(CC) $(CFLAGS) $(SANITIZE) main.c $(LDFLAGS) $(LDFLAGSLIB) -I$(LIBFT_DIR)
endif

$(OBJS):	%.o: %.c $(HEAD) $(LIBFT)
			@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES) -I$(LIBFT_DIR) 
			@echo "\x1b[1m\x1b[32m-> $@ compiled\x1b[0m"

clean:
	@(cd $(LIBFT_DIR) && $(MAKE) $@)
	@$(RM) $(OBJS)
	@echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

fclean: clean
	@(cd $(LIBFT_DIR) && $(MAKE) $@)
	@$(RM) $(NAME) a.out
	@echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

re: fclean all

.PHONY:		all exec clean fclean re bonus
