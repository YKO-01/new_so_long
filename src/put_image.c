/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:54:55 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/10 14:11:10 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_img(t_mlx *mlx, t_item *img)
{
	if (!img->s)
		mlx_destroy_image(mlx->mlx, img->p);
	else if (!img->e)
	{
		mlx_destroy_image(mlx->mlx, img->p);
		mlx_destroy_image(mlx->mlx, img->s);
	}
	else if (!img->c)
	{
		mlx_destroy_image(mlx->mlx, img->p);
		mlx_destroy_image(mlx->mlx, img->s);
		mlx_destroy_image(mlx->mlx, img->e);
	}
	else if (!img->w)
	{
		mlx_destroy_image(mlx->mlx, img->p);
		mlx_destroy_image(mlx->mlx, img->s);
		mlx_destroy_image(mlx->mlx, img->e);
		mlx_destroy_image(mlx->mlx, img->c);
	}
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
}

int	init_image(t_mlx *game, t_item *img)
{
	t_img	st[5];

	st[0].src = "./textures/player.xpm";
	st[1].src = "./textures/space.xpm";
	st[2].src = "./textures/exit.xpm";
	st[3].src = "./textures/coin.xpm";
	st[4].src = "./textures/wall.xpm";
	img->p = mlx_xpm_file_to_image(game->mlx, st[0].src, &st[0].w, &st[0].h);
	if (!img->p)
		return (ft_putstr_fd("Error in src img\n", 2), free_img(game, img), 0);
	img->s = mlx_xpm_file_to_image(game->mlx, st[1].src, &st[1].w, &st[1].h);
	if (!img->s)
		return (ft_putstr_fd("Error in src img\n", 2), free_img(game, img), 0);
	img->e = mlx_xpm_file_to_image(game->mlx, st[2].src, &st[2].w, &st[2].h);
	if (!img->e)
		return (ft_putstr_fd("Error in src img\n", 2), free_img(game, img), 0);
	img->c = mlx_xpm_file_to_image(game->mlx, st[3].src, &st[3].w, &st[3].h);
	if (!img->c)
		return (ft_putstr_fd("Error in src img\n", 2), free_img(game, img), 0);
	img->w = mlx_xpm_file_to_image(game->mlx, st[4].src, &st[4].w, &st[4].h);
	if (!img->w)
		return (ft_putstr_fd("Error in src img\n", 2), free_img(game, img), 0);
	return (1);
}

void	ft_putimage(t_mlx *game, t_data *data, t_item *img)
{
	int	i;
	int	j;
	int	ar[2];

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		ar[0] = i;
		while (data->map[i][++j])
		{
			ar[1] = j;
			isolate_image(game, img, data->map[i][j], ar);
		}
	}
}

void	isolate_image(t_mlx *game, t_item *img, char c, int *ar)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		img->s, ar[1] * game->x, ar[0] * game->y);
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			img->w, ar[1] * game->x, ar[0] * game->y);
	else if (c == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			img->p, ar[1] * game->x, ar[0] * game->y);
	}
	else if (c == 'E')
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			img->e, ar[1] * game->x, ar[0] * game->y);
	}
	else if (c == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			img->c, ar[1] * game->x, ar[0] * game->y);
	}
}
