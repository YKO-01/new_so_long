/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:06 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/04/08 18:19:33 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*newlist(int x, int y)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (0);
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

void	lstadd(t_map *lst, t_map *newnode)
{
	t_map	*tmp;

	if (!newnode || !lst)
		return ;
	tmp = lst;
	while (tmp->next)
	{
		if (tmp->x == newnode->x && tmp->y == newnode->y)
		{
			free(newnode);
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp->x == newnode->x && tmp->y == newnode->y)
	{
		free(newnode);
		return ;
	}
	tmp->next = newnode;
}

void	lstfree(t_map *lst)
{
	t_map	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
