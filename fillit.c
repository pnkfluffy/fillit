/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelee <lelee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 14:37:05 by lelee             #+#    #+#             */
/*   Updated: 2019/08/24 16:30:36 by lelee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		saveprint(char **grid)
{
	int		i;
	int		j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			ft_putchar(grid[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

/*
**	recursive function which checks each possible placement for each block.
**	places tetrominos in the order they are given starting from the top left.
**	each time the board is not completed and there is no more space for
**	tetrominos, the function recursively backtracks, removing the last pice and
**	looking for a new place for it. l_bdnry and d_bdnry check the left and
**	downwards boundries to ensure there is no attempt to access out of boundry
**	memory. if all blocks are placed, saveprint() is called to print the state
**	of the grid and 1 is returned. else 0 is returned and the function is called
**	 again with a larger grid size.
*/

int			fillit(t_tetro *curr, char **grid, int y, int x)
{
	if (!curr)
	{
		saveprint(grid);
		grid_free(grid);
		free(grid);
		return (1);
	}
	if (!grid[y])
		return (0);
	if (grid[y][x] == '.' && l_bndry(x, curr) &&
	d_bndry(y, curr, ft_strlen(grid[0])))
		if (isfree(curr, grid, y, x))
		{
			if (fillit(curr->next, place(curr, grid, y, x), 0, 0))
				return (1);
			else
				clear(curr, grid, y, x);
		}
	return (grid[y][x + 1] != '\0' ? fillit(curr, grid, y, ++x) : \
	fillit(curr, grid, ++y, 0));
}
