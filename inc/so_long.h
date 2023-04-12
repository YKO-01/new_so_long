/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:47 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/12 17:08:11 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
}				t_mlx;

typedef struct s_map
{
	int				x;
	int				y;
	struct s_map	*next;
}	t_map;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_data
{
	char	**map;
	int		w;
	int		h;
}	t_data;

typedef struct s_image
{
	char	*src;
	int		w;
	int		h;	
}	t_img;

typedef struct s_count
{
	int	e;
	int	c;
}	t_count;

typedef struct s_item
{
	void	*p;
	void	*s;
	void	*e;
	void	*c;
	void	*w;
}	t_item;

typedef struct s_full
{
	t_mlx	*game;
	t_data	*data;
	t_item	*img;
	t_pos	p;
	int		c;
	int		i;
}	t_full;

/* ========= main functions ========= */

void	so_long(t_data *data);
void	free_2d_array(char **ar);

/* ========= handling map functions ========= */

int		map_shape(char **map);
int		scan_items(char **map, char c);
int		scan_wall(t_data *data);
int		check_map(t_data *data);
void	handling_map(t_data *data, t_count *count);

/* ========= utils functions ========= */

int		check_arg(char *ptr);
t_pos	*pos_element(t_pos *pos, char **map, char c);
int		count_hieght(int fd);
void	read_line(t_data *data, int fd, int i, int j);
char	**read_map(char *file, t_data *data);
t_map	*newlist(int x, int y);
void	lstadd(t_map *lst, t_map *newnode);
void	lstfree(t_map *lst);

/* ========= event functions ========= */

int		ft_key_move(int key, t_full *full);
int		exit_from_game(t_full *full);
int		check_valid_move(t_full *full, int y, int x);
void	check_exit(t_full *full, int y, int x);

/* ========= images functions ========= */

void	free_img(t_mlx *mlx, t_item *img);
void	ft_putimage(t_mlx *game, t_data *data, t_item *img);
int		init_image(t_mlx *game, t_item *img);
void	isolate_image(t_mlx *game, t_item *img, char c, int *ar);

#endif
