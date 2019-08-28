/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelee <lelee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 12:12:03 by lelee             #+#    #+#             */
/*   Updated: 2019/08/24 16:32:47 by lelee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		grid_free(char **grid)
{
	int i;
	int size;

	i = -1;
	size = ft_strlen(grid[0]);
	while (++i < size)
		ft_strdel(&grid[i]);
	ft_memdel((void**)grid);
}

void		deletelist(struct s_tetro **curr)
{
	struct s_tetro *tet;
	struct s_tetro *next;

	tet = *curr;
	while (tet != NULL)
	{
		next = tet->next;
		free(tet);
		tet = next;
	}
	*curr = NULL;
}

char		*grid_mark(int size)
{
	char	*dot;
	int		i;

	i = -1;
	if (!(dot = ft_strnew((size_t)size)))
		return (NULL);
	dot[size--] = '\0';
	while (i < size)
		dot[++i] = '.';
	return (dot);
}

char		**ft_grid(int size)
{
	char	**grid;
	int		i;

	if (!(grid = (char **)ft_memalloc((size + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (++i < size)
		grid[i] = grid_mark(size);
	return (grid);
}
