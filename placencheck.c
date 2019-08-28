/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placencheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelee <lelee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:02:37 by jfelty            #+#    #+#             */
/*   Updated: 2019/08/24 16:30:51 by lelee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char g_letter = 'A' - 1;

int		isfree(t_tetro *curr, char **grid, int y, int x)
{
	if (grid[y + (curr->cords[1])][x + (curr->cords[0])] == '.' &&
	grid[y + (curr->cords[3])][x + (curr->cords[2])] == '.' &&
	grid[y + (curr->cords[5])][x + (curr->cords[4])] == '.')
		return (1);
	return (0);
}

char	**place(t_tetro *curr, char **grid, int y, int x)
{
	g_letter++;
	grid[y][x] = g_letter;
	grid[y + (curr->cords[1])][x + (curr->cords[0])] = g_letter;
	grid[y + (curr->cords[3])][x + (curr->cords[2])] = g_letter;
	grid[y + (curr->cords[5])][x + (curr->cords[4])] = g_letter;
	return (grid);
}

char	**clear(t_tetro *curr, char **grid, int y, int x)
{
	g_letter--;
	grid[y][x] = '.';
	grid[y + (curr->cords[1])][x + (curr->cords[0])] = '.';
	grid[y + (curr->cords[3])][x + (curr->cords[2])] = '.';
	grid[y + (curr->cords[5])][x + (curr->cords[4])] = '.';
	return (grid);
}

int		l_bndry(int x, t_tetro *curr)
{
	if (x < curr->left)
		return (0);
	return (1);
}

int		d_bndry(int y, t_tetro *curr, int gridsize)
{
	if (gridsize - y <= curr->down)
		return (0);
	return (1);
}
