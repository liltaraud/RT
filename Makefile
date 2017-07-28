# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/29 16:17:39 by ltaraud           #+#    #+#              #
#    Updated: 2017/05/23 21:43:17 by ltaraud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG = yes
NAME = rt
CC = gcc
LIBS_DIR = 42_RT_libs
SDL_DIR = SDL2
FREETYPE_DIR = freetype
TTF_DIR = SDL2_ttf
SDL_SRC_DIR = $(LIBS_DIR)/SDL2-2.0.5
FREETYPE_SRC_DIR = $(LIBS_DIR)/freetype-2.7.1
TTF_SRC_DIR = $(LIBS_DIR)/SDL2_ttf-2.0.14
SCENE_LIB = libscene
SCENE_LIB_INC = $(SCENE_LIB)/includes
SDL_INC = $(SDL_DIR)/include/SDL2
TTF_INC = $(TTF_DIR)/include/SDL2


FLAG_TTF =	-L $(TTF_DIR)/lib -lSDL2_ttf
FLAG_SDL =	`$(LIBS_DIR)/SDL2/sdl2-config --cflags --static-libs`
INC_PATH =	includes
SRC_PATH =	src
OBJ_PATH =	obj
LIB_NAME =	libft

SRC_NAME =	main.c\
			switch_env.c\
			dump_var.c\
			obj_dump.c\
			manage_cam_scn.c\
			camera_init.c\
			float4_vec.c\
			vec_float4.c\
			initialization.c\
			obj_init.c\
			obj_table_init.c\
			lgt_init.c\
			lgt_table_init.c\
			render.c\
			widgets_add.c\
			gui_init.c\
			gui_draw.c\
			rotation.c\
			sdl_hook.c\
			sdl_init.c\
			sdl_loop.c\
			cl_write_tables.c\
			skybox.c\
			terminate.c\
			vec_cross.c\
			vec_div_i.c\
			vec_dot.c\
			vec_length.c\
			vec_minus.c\
			vec_normalize.c\
			vec_opposite.c\
			vec_plus.c\
			vec_times_i.c\
			build_kernel.c\
			load_kernel.c\
			cl_flush.c\
			cl_init.c\
			cl_data_release.c\
			check_ocl_error.c\
			ocl_context_callback.c\
			cl_objects_init.c\
			cl_update_camera.c\
			cl_get_ws.c\
			interface_draw.c\
			interface_move.c\
			key_event.c\
			mouse_hook.c\
			animate.c\

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
LIBS = $(LIB_NAME)/$(LIB_NAME).a


CPPFLAGS = -I $(INC_PATH) -I $(LIB_NAME)/$(INC_PATH) -I $(SDL_INC) -I $(TTF_INC) -I libscene/includes/ # new
CLFLAGS = -L $(LIB_NAME) -$(subst ib,,$(LIB_NAME)) $(FLAG_SDL) $(FLAG_TTF) libscene/libscene.a
UNAME := $(Shell uname)


ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Werror -Wextra -g3
else
	CFLAGS = -Wall -Werror -Wextra
endif

ifeq ($(UNAME), Linux)
	LINK_FLAGS = -lOpenCL
else
	LINK_FLAGS = -framework opencl
endif

.PHONY: all clean fclean re libsclean norme

all: $(LIBS) $(NAME)

ifeq ($(DEBUG), yes)
		@echo "\x1B[01;91m -------------------------[DEBUG MODE ACTIVATED]------------------------- \x1B]0m"
else
		@echo "\x1B[01;93m ------------------------[RELEASE MODE ACTIVATED]------------------------ \x1B]0m"
endif

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CLFLAGS) $(LINK_FLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBS): config
	make -C $(LIB_NAME)
	make -C $(SCENE_LIB)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

config:
	test -d $(LIBS_DIR) || git clone https://github.com/K3ungy/42_RT_libs.git $(LIBS_DIR)
	(test -d $(LIBS_DIR) && test -d $(SDL_DIR) && test -d $(FREETYPE_DIR) && test -d $(TTF_DIR)) || make -C $(LIBS_DIR)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(SCENE_LIB) clean

fclean:
	rm -rf $(OBJ_PATH)
	rm -rf $(SDL_DIR)
	rm -rf $(FREETYPE_DIR)
	rm -rf $(TTF_DIR)
	rm -fv $(NAME)
	make -C $(SCENE_LIB) fclean
	make -C $(LIB_NAME) fclean
	rm -rf $(LIBS_DIR)

re: fclean all

norme:
	norminette $(SRC)
	norminette $(INC_PATH)/*.h
