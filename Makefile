# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 15:16:54 by lbrandy           #+#    #+#              #
#    Updated: 2021/03/24 10:56:16 by lbrandy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -Imlx
CC = gcc
LIB = libmlx.dylib
LIBFT_DIR = ./source/libft/
LIBFT = ./source/libft/libft.a
SRCS = main.c mlx_help.c not_texture_ray.c texture_reading.c\
	   paint_sprites.c ft_pars_all.c argv_check.c pars_color.c\
	   pars_file.c pars_map.c pars_map_copy_mainmap.c\
	   pars_map_flood.c pars_map_part_2.c pars_resol.c\
	   pars_textures.c pars_utils.c error_handler.c screen_save.c\
	   ft_check_struct.c calc_raycast.c drawing.c sprite_array.c
OBJDIR = obj/
OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME):$(OBJDIR) $(OBJS) cub3d.h
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -Lmlx -lmx -framework OpenGL -framework Appkit $(LIB) $(LIBFT) $(SRCS) -o $(NAME)
$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
