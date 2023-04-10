/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:08:06 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/10 14:11:37 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_2d_array(char **ar)
{
	int	i;

	i = -1;
	while (ar[++i])
		free(ar[i]);
	free(ar);
}

void	so_long(t_data *data)
{
	t_mlx	game;
	t_item	img;
	t_full	full;

	game.mlx = mlx_init();
	if (game.mlx == NULL)
		return ;
	game.x = 50;
	game.y = 50;
	game.mlx_win = mlx_new_window(game.mlx, data->w * game.x,
			data->h * game.y, "so_long");
	if (!game.mlx_win)
		return ;
	if (!init_image(&game, &img))
		return ;
	ft_putimage(&game, data, &img);
	full.game = &game;
	full.data = data;
	full.img = &img;
	full.c = scan_items(full.data->map, 'C');
	full.p = *(pos_element(&full.p, full.data->map, 'P'));
	full.i = 0;
	mlx_hook(full.game->mlx_win, 2, 0, ft_key_move, &full);
	mlx_hook(full.game->mlx_win, 17, 0, exit_from_game, &full);
	mlx_loop(game.mlx);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Error\n", 2), 0);
	if (!check_arg(av[1]))
		return (ft_putstr_fd("Error\n", 2), 0);
	data.map = read_map(av[1], &data);
	if (!data.map)
		return (ft_putstr_fd("Error\n", 2), 0);
	if (!check_map(&data))
	{
		free_2d_array(data.map);
		return (ft_putstr_fd("Error\n", 2), 0);
	}
	if (data.h > 38 || data.w > 38)
	{
		free_2d_array(data.map);
		return (ft_putstr_fd("Error\n", 2), 0);
	}
	so_long(&data);
	return (0);
}
