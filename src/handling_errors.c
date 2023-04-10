/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:19:53 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/08 17:56:08 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_shape(char	**map)
{
	int	index;
	int	len0;
	int	len1;

	index = -1;
	while (map[++index])
	{
		len0 = ft_strlen(map[index]);
		if (map[index + 1])
		{
			len1 = ft_strlen(map[index + 1]);
			if (len0 != len1)
				return (0);
		}
	}
	return (1);
}

int	scan_items(char **map, char c)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == c)
				count++;
		}
	}
	return (count);
}

int	scan_wall(t_data *data)
{
	int	i;

	i = -1;
	while (data->map[0][++i])
	{
		if (data->map[0][i] != '1')
			return (0);
	}
	i = -1;
	while (data->map[++i])
	{
		if (data->map[i][0] != '1')
			return (0);
		if (data->map[i][data->w - 1] != '1')
			return (0);
	}
	i = -1;
	while (data->map[data->h - 1][++i])
	{
		if (data->map[data->h - 1][i] != '1')
			return (0);
	}
	i = -1;
	return (1);
}

int	check_map(t_data *data)
{
	t_count	count;
	int		i;
	int		j;

	if (!map_shape(data->map) || !scan_wall(data))
		return (0);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] != 'P' && data->map[i][j] != 'C'
				&& data->map[i][j] != 'E' && data->map[i][j] != '0'
				&& data->map[i][j] != '1')
				return (0);
		}
	}
	count.e = 0;
	count.c = 0;
	handling_map(data, &count);
	if (scan_items(data->map, 'P') != 1 || scan_items(data->map, 'E') != 1
		|| count.e != 1 || count.c < 1 || scan_items(data->map, 'C') != count.c)
		return (0);
	return (1);
}

void	handling_map(t_data *data, t_count *count)
{
	t_map	*first;
	t_map	*cur;
	t_pos	player;

	player = *(pos_element(&player, data->map, 'P'));
	first = newlist(player.x, player.y);
	cur = first;
	while (cur)
	{
		if (data->map[cur->y][cur->x] == 'E')
			count->e++;
		else if (data->map[cur->y][cur->x] == 'C')
			count->c++;
		if (data->map[cur->y][cur->x + 1] != '1')
			lstadd(first, newlist(cur->x + 1, cur->y));
		if (data->map[cur->y + 1][cur->x] != '1')
			lstadd(first, newlist(cur->x, cur->y + 1));
		if (data->map[cur->y][cur->x - 1] != '1')
			lstadd(first, newlist(cur->x - 1, cur->y));
		if (data->map[cur->y - 1][cur->x] != '1')
			lstadd(first, newlist(cur->x, cur->y - 1));
		cur = cur->next;
	}
	lstfree(first);
}
