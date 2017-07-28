# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/30 18:45:43 by ttrossea          #+#    #+#              #
#    Updated: 2017/05/23 17:19:08 by ttrossea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libscene.a
SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I includes \
		   -I ../libft/includes \
		   -I ../SDL2/include/SDL2

SRCS=parse_scene_file.c \
	scn_jmp_next_line.c \
	make_info.c \
	free_scene.c \
	new_scene.c \
	process_tag.c \
	tag_cam.c \
	tag_lgt.c \
	tag_obj.c \
	object_sphere.c \
	object_cone.c \
	object_cylindre.c \
	object_plane.c \
	object_paraboloid.c \
	scn_parse_float4.c \
	scn_parse_float.c \
	new_mark.c \
	rotate_pt.c \
	init_mtl.c \
	verify_mtl.c

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
	ar rc $(NAME) $(OBJ) ../libft/libft.a
	ranlib $(NAME)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)
fclean: clean
	rm -rf $(NAME)
re: fclean all
