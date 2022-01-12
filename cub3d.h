/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:05:58 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 19:05:56 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./source/libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>

typedef struct s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				endian;
}					t_win;

typedef struct s_draw
{
	int				line_h;
	int				start;
	int				end;
	int				color;
	int				tex_width;
	int				tex_height;
	double			wall_x;
	double			step;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	double			ms;
	double			rs;
}					t_draw;

typedef struct s_raycast
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			walldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}					t_raycast;

typedef struct s_pos
{
	int				map_width;
	int				map_height;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_pos;

typedef struct s_textures
{
	int				x;
	int				y;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*s_texture;
	int				f;
	int				c;
}					t_textures;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
}					t_sprite;

typedef struct s_datasprite
{
	t_sprite		*sprites;
	int				count_sprites;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				tex_height;
	int				tex_width;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				color;
	double			*z_buffer;
}					t_datasprite;

typedef struct s_datatext
{
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				endian;
	int				height;
	int				width;
}					t_datatext;

typedef struct s_all
{
	t_datatext		*no;
	t_datatext		*so;
	t_datatext		*we;
	t_datatext		*ea;
	t_datatext		*s;
	t_win			*win;
	t_textures		*textures;
	t_pos			*pos;
	t_raycast		*raycast;
	t_draw			*draw;
	t_datasprite	*data_sprite;
	char			**map;
	char			dir;
}					t_all;

void				my_mlx_pixel_put(t_all *all, int x, int y, int color);
int					raycasting(t_all *all);
void				draw_frame(t_all *all);
void				reading_textures(t_all *all);
void				draw_wall(t_all *all, t_draw *d, int *y, int x);
void				init_mlx(t_win *w, t_all *all, int argc);
void				draw_sprites(t_all *all);
void				draw_sprite(t_datasprite *s, t_textures *res,
						t_datatext *tex, t_all *all);
void				init_sprite(t_all *all);
void				quick_sort(t_sprite *sprite, int start, int end);
void				array_of_sprites(t_all *all, int i);
int					count_of_sprites(char **map);
int					argv_check(int argc, char **argv);
t_all				*pars_all(char *name_of_file);
void				check_color(t_textures *tex, int type);
void				skip(char **s, int flag);
void				pars_colors(t_textures *tex, int type, char *s);
t_list				*pars_struct(t_textures *t, t_list **list);
void				pars_file(t_list **list, t_all *all);
void				fill_map(t_list *list, t_all *all);
t_pos				*pars_map(t_list *list, t_all *all);
char				**copy_map(t_pos *p, t_all *all);
void				free_new_map(t_pos *p, char **new_map);
void				init_dir(t_pos *pos, char temp);
void				init_pos(t_all *all, t_pos *pos);
void				check_up_down(char **map, int i, int h);
void				check_boundary(t_all *all, char **map, t_pos *pos);
int					max_width_map(char **map);
void				flood_fill(char **map, t_pos *p, int x, int y);
void				flood(t_pos *pos, t_all *all);
void				pars_res(char *res, t_textures *t, int len);
void				skip_spaces(char **s);
void				check_trash_str(char *s, t_textures *t);
int					check_full_struct(t_textures *t);
void				init_struct(t_textures *t);
void				pars_textures(t_textures *text, int side, char *s);
void				check_xpm(char *s);
void				check_textures(t_textures *tex, int side);
void				error_handler(char *str);
void				ft_lstfree_cont(void *content);
int					my_exit_from_game(void);
void				screen_save(t_all *all, int argc);
int					ft_press_but(int keycode, t_all *all);
int					ft_release_but(int keycode, t_all *all);
int					drawing(int keycode, t_all *all);
int					len_number(char *s, int flag);
void				ft_filling_map(t_list *list, t_all *all, int count);
void				init_step(t_raycast *ray, t_pos *pos);
void				init_raycast(t_raycast *raycast, int x, int w, t_pos *pos);
void				calc_dda(t_raycast *ray, char **map, t_pos *p);
void				init_draw(t_draw *draw, t_raycast *r, t_all *all, t_pos *p);
void				init_sprite_dist(t_datasprite *data_sprite,
						t_pos *pos, t_all *all);
void				calculate_draw(t_datasprite *sprite, t_textures *res);
void				calc_sprite(t_datasprite *sprite, int i,
						t_pos *pos, t_textures *res);

#endif
