# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/02/01 13:37:28 by bajeanno         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Werror -Wall -Wextra -I libft/head -I libft -I . -I minilibx-linux #-fsanitize=address

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a
MLX = libmlx.dylib

SRC =	fdf.c fdf_parsing.c fdf_map_utils.c fdf_isometrical.c fdf_drawing.c fdf_center_in_frame.c \
		fdf_image_handling.c fdf_mlx_config.c fdf_parsing_utils.c fdf_update_frame.c
 
BONUS_SRC = 

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d)) $(addprefix obj/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : create_obj_folder lib mlx
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lm -Lminilibx-linux -lmlx -lXext -lX11 -o $(NAME)

bonus : create_obj_folder lib
	@$(MAKE) $(NAME)

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile $(LIBFT)
	cc $(FLAGS) -c $< -MD -I libft/head -I head -I minilibx-linux -o $@

lib : libft
	@$(MAKE) -C libft

mlx : $(MLX)

$(MLX) :
	$(MAKE) -C minilibx-linux

libft :
	git clone git@github.com:fan2bolide/libft.git

run : all
	./$(NAME)

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	$(MAKE) clean -C minilibx-linux
	
fclean : clean
	$(RM) libmlx.dylib
	$(RM) $(NAME)
	$(RM) .main .bonus
	$(MAKE) fclean -C libft
	$(MAKE) clean -C minilibx-linux

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all run re clean fclean bonus rm_lib create_obj_folder

-include $(DEPENDS)