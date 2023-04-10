/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:31:26 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/10 14:08:54 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_from_game(t_full *full)
{
	free_2d_array(full->data->map);
	mlx_destroy_image(full->game->mlx, full->img->p);
	mlx_destroy_image(full->game->mlx, full->img->s);
	mlx_destroy_image(full->game->mlx, full->img->e);
	mlx_destroy_image(full->game->mlx, full->img->c);
	mlx_destroy_image(full->game->mlx, full->img->w);
	mlx_destroy_window(full->game->mlx, full->game->mlx_win);
	exit(0);
}

int	check_valid_move(t_full *full, int y, int x)
{
	if (full->data->map[y][x] == '1')
		return (0);
	else if (full->data->map[y][x] == 'C' && full->c > 0)
	{
		full->data->map[y][x] = '0';
		full->c--;
	}
	else if (full->data->map[y][x] == 'E')
	{
		if (!full->c)
			exit_from_game(full);
		else
		{
			mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
				full->img->s, full->p.x * full->game->x,
				full->p.y * full->game->y);
			mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
				full->img->s, x * full->game->x, y * full->game->y);
			mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
				full->img->e, x * full->game->x, y * full->game->y);
		}
	}
	return (1);
}

void	check_exit(t_full *full, int y, int x)
{
	if (full->data->map[full->p.y][full->p.x] == 'E')
	{
		mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
			full->img->s, full->p.x * full->game->x, full->p.y * full->game->y);
		mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
			full->img->e, full->p.x * full->game->x, full->p.y * full->game->y);
	}
	else
	{	
		mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
			full->img->s, x * full->game->x, y * full->game->y);
		mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
			full->img->s, full->p.x * full->game->x, full->p.y * full->game->y);
	}
	mlx_put_image_to_window(full->game->mlx, full->game->mlx_win,
		full->img->p, x * full->game->x, y * full->game->y);
	ft_printf("%d\n", ++full->i);
}		

int	ft_key_move(int key, t_full *full)
{	
	if (key == 13 && check_valid_move(full, full->p.y - 1, full->p.x))
	{	
		check_exit(full, full->p.y - 1, full->p.x);
		full->p.y--;
	}
	else if (key == 1 && check_valid_move(full, full->p.y + 1, full->p.x))
	{
		check_exit(full, full->p.y + 1, full->p.x);
		full->p.y++;
	}
	else if (key == 2 && check_valid_move(full, full->p.y, full->p.x + 1))
	{
		check_exit(full, full->p.y, full->p.x + 1);
		full->p.x++;
	}
	else if (key == 0 && check_valid_move(full, full->p.y, full->p.x - 1))
	{
		check_exit(full, full->p.y, full->p.x - 1);
		full->p.x--;
	}
	else if (key == 53)
		exit_from_game(full);
	return (0);
}
