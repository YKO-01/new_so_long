/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:42:33 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/12 17:10:31 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_arg(char *ptr)
{
	char	**arg;
	char	**pth;
	int		i;
	int		j;

	pth = ft_split(ptr, '/');
	arg = ft_split(ptr, '.');
	j = -1;
	while (pth[++j])
		;
	j--;
	i = -1;
	while (arg[++i])
		;
	i--;
	if (!ft_strncmp(arg[i], "ber", ft_strlen(arg[i]))
		&& ft_strncmp(pth[j], ".ber", ft_strlen(pth[j])))
	{
		free_2d_array(arg);
		free_2d_array(pth);
		return (1);
	}
	free_2d_array(arg);
	free_2d_array(pth);
	return (0);
}

t_pos	*pos_element(t_pos *pos, char **map, char c)
{
	pos->y = -1;
	while (map[++pos->y])
	{
		pos->x = -1;
		while (map[pos->y][++pos->x])
		{
			if (map[pos->y][pos->x] == c)
				return (pos);
		}
	}
	free_2d_array(map);
	ft_putstr_fd("Error\n", 2);
	exit(0);
}

int	count_hieght(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	free(line);
	close(fd);
	if (count <= 2)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (count);
}

void	read_line(t_data *data, int fd, int i, int j)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->w = ft_strlen(line) - 1;
		data->map[i] = malloc(data->w + 1);
		if (!data->map[i])
		{
			while (i-- >= 0)
				free(data->map[i]);
			free(data->map);
			exit(1);
		}
		j = -1;
		while (line[++j] && line[j] != '\n')
			data->map[i][j] = line[j];
		data->map[i][j] = 0;
		i++;
		free(line);
	}
	free(line);
	data->map[i] = 0;
}

char	**read_map(char *file, t_data *data)
{
	int	i;
	int	j;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	data->h = count_hieght(fd);
	data->map = (char **)malloc(sizeof(char *) * (data->h + 1));
	if (!data->map)
		return (0);
	fd = open(file, O_RDONLY);
	i = 0;
	j = -1;
	read_line(data, fd, i, j);
	close(fd);
	return (data->map);
}
