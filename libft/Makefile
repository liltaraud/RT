# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/29 16:17:39 by ltaraud           #+#    #+#              #
#    Updated: 2017/05/22 22:57:12 by ttrossea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_PATH = src
OBJ_PATH = obj
INC_PATH = includes
SRCS = ft_atoi.c\
	   ft_bzero.c\
	   ft_isalnum.c\
	   ft_isalpha.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprint.c\
	   ft_itoa.c\
	   ft_memalloc.c\
	   ft_memccpy.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_memcpy.c\
	   ft_memset.c\
	   ft_putchar.c\
	   ft_putstr.c\
	   ft_strcat.c\
	   ft_strchr.c\
	   ft_strclr.c\
	   ft_strcmp.c\
	   ft_strcpy.c\
	   ft_strdup.c\
	   ft_strjoin.c\
	   ft_strlen.c\
	   ft_memdel.c\
	   ft_strncat.c\
	   ft_strncmp.c\
	   ft_strncpy.c\
	   ft_strrchr.c\
	   ft_strnew.c\
	   ft_strstr.c\
	   ft_tolower.c\
	   ft_toupper.c\
	   ft_strnstr.c\
	   ft_strequ.c\
	   ft_strnequ.c\
	   ft_strsub.c\
	   ft_strdel.c\
	   ft_putstr_fd.c\
	   ft_putendl.c\
	   ft_putchar_fd.c\
	   ft_putendl_fd.c\
	   ft_strlcat.c\
	   ft_striter.c\
	   ft_striteri.c\
	   ft_strtrim.c\
	   ft_strsplit.c\
	   ft_putnbr.c\
	   ft_putnbr_fd.c\
	   ft_strmap.c\
	   ft_strmapi.c\
	   ft_memmove.c\
	   ft_lstnew.c\
	   ft_lstdelone.c\
	   ft_lstdel.c\
	   ft_lstadd.c\
	   ft_lstiter.c\
	   ft_lstmap.c\
	   ft_min.c\
	   ft_max.c\
	   get_next_line.c\
	   ft_read_file.c\
	   free_ptr.c\
	   ft_realloc.c\
	   ft_strnccpy.c\
	   cparg.c\
	   ft_atod.c\
	   is_pagin.c\
	   ft_strchrlast.c\
	   next_line.c\
	   cpline.c\
	   next_arg.c\
	   is_nbr.c\
	   is_space.c\
	   ft_atof.c\
	   push_elm.c\
	   add_elm.c\
	   new_elm.c\
	   count_elm.c

HEADER = libft.h

OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJS))
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))
CC = gcc
INC = $(addprefix $(INC_PATH)/,$(HEADER))
CFLAGS = -Werror -Wextra -Wall -g3

.PHONY: all clean fclean re
.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INC_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
