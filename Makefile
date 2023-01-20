# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/01/20 05:10:13 by bajeanno         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Werror -Wall -Wextra -I libft/head -I libft -I . -I mlx

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a
MLX = libmlx.dylib

SRC =	fdf.c fdf_parsing.c fdf_map_utils.c fdf_isometrical.c fdf_drawing.c fdf_center_in_frame.c \
		fdf_image_handling.c fdf_mlx_config.c fdf_parsing_utils.c
 
BONUS_SRC = 

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d)) $(addprefix obj/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : lib mlx .main
	@$(MAKE) $(NAME)

.main :
	touch .main
	$(RM) .bonus

$(NAME): $(OBJ) $(LIBFT) .main
	$(CC) $(OBJ) $(LIBFT) $(DEBUG_FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus : create_obj_folder lib .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LIBFT) $(FLAGS) -o $(NAME)
	touch .bonus
	$(RM) .mandatory

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile
	cc -Wall -Wextra -Werror -c $< -MD -I libft/head -I head -I mlx -o $@

debug : lib
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

lib : libft
	@$(MAKE) -C libft

mlx : $(MLX)

$(MLX) :
	$(MAKE) -C mlx

libft :
	git clone git@github.com:fan2bolide/libft.git

run : all
	./$(NAME)

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx
	
fclean : clean
	$(RM) libmlx.dylib
	$(RM) $(NAME)
	$(RM) .main .bonus
	$(MAKE) fclean -C libft
	$(MAKE) clean -C mlx

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all run re clean fclean bonus rm_lib

-include $(DEPENDS)