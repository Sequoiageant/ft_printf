# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/04/30 19:38:54 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include color.mk

NAME	= libftprintf.a
MAIN	= main.c

# ---------------- CC ---------------- #

CC	= clang

ifeq ($(err), no)
	CFLAGS += -Wall
	CFLAGS += -Wextra
else
	CFLAGS += -Wall
	CFLAGS += -Wextra
	CFLAGS += -Werror
endif

ifeq ($(debug), 0)
	CFLAGS += -g3
else ifeq ($(debug), 1)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
else ifeq ($(debug), 2)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -ansi
	CFLAGS += -pedantic
else ifeq ($(debug), 3)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -ansi
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -ansi
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
	CFLAGS += -Weverything
endif

# ---------------- SRC --------------- #

# Debug Sources
# SRCS += debug.c

# Main Sources
SRCS += ft_printf.c
SRCS += ft_printf_conversions.c
SRCS += ft_printf_itoas.c
SRCS += ft_printf_handle.c
SRCS += ft_printf_utils.c

vpath %.c ./


# ---------------- INC --------------- #

INCLUDES 	=	./
HEAD 		= $(INCLUDES)ft_printf.h
ALL_INC		= -I$(INCLUDES) -I$(LIBFT_DIR)

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))

# ---------------- LIB --------------- #

LIBFT_DIR 	= ./libft/
LIBFT 		= $(LIBFT_DIR)libft.a
ALL_LIB		= -L./ -lftprintf -L$(LIBFT_DIR) -lft

# --------- Compilation Rules -------- #

all: $(NAME)

fast:
	$(MAKE) re -j8

$(NAME):	$(LIBFT) $(OBJS) 
			ar rcs $@ $^
			ranlib $@
			echo "$(_BOLD)$(_YELLOW)--> Creating $@...$(_END)"

exec :		$(NAME) $(MAIN)
			$(CC) $(CFLAGS) $(MAIN) $(ALL_LIB) $(ALL_INC) -o $@
			echo "$(_BOLD)$(_YELLOW)==> $@ made$(_END)"

$(OBJS):	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@ $(ALL_INC) 
			echo "$(_BOLD)$(_GREEN)--> $@ made$(_END)"

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(_BOLD)$(_YELLOW)--> $@ made$(_END)"


FORCE:


clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -R $(DIR_OBJS)
	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(RM) exec
	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

re: fclean
	$(MAKE)

.PHONY:		all exec clean fclean re bonus
.SILENT:	$(OBJS) $(DIR_OBJS) $(NAME) $(LIBFT) exec