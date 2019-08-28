/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelee <lelee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 02:15:28 by lelee             #+#    #+#             */
/*   Updated: 2019/08/24 16:30:57 by lelee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		boundary(t_tetro *tet, int *cords)
{
	int		i;

	i = 0;
	if (cords[0] < i)
		i = cords[0];
	if (cords[2] < cords[0])
		i = cords[2];
	if (cords[4] < cords[2])
		i = cords[4];
	tet->left = -i;
	i = 0;
	if (cords[1] > i)
		i = cords[1];
	if (cords[3] > cords[1])
		i = cords[3];
	if (cords[5] > cords[3])
		i = cords[5];
	tet->down = i;
}

void		addtolist(t_tetro *str, t_tetro *firsttet)
{
	while (firsttet->next)
		firsttet = firsttet->next;
	firsttet->next = str;
	str->next = NULL;
}

/*
**	is called by makelist to populate the rest of the newtet
**	struct with coordinates.
*/

t_tetro		*listcoord(char *str, int len, int holdx, t_tetro *newtet)
{
	int		subx;
	int		y;
	int		cordnum;

	subx = holdx;
	y = 0;
	cordnum = -1;
	while (--len > 0)
	{
		subx++;
		if (*str == '\n')
		{
			y++;
			subx = -1;
		}
		if (*str == '#')
		{
			newtet->cords[++cordnum] = (subx - holdx);
			newtet->cords[++cordnum] = (y);
		}
		str++;
	}
	boundary(newtet, newtet->cords);
	return (newtet);
}

/*
**  finds the first '#' character. uses it as a reference point in order to
**  make a list of coordinates relative to the first position. allocates memory
**  then passes the string into listcoords to map out the coordinate positions.
*/

t_tetro		*makelist(char *str, int len)
{
	t_tetro *newtet;
	int		holdx;

	holdx = 0;
	while (*str++ != '#')
	{
		len--;
		holdx++;
		if (*str == '\n')
			holdx = -1;
	}
	if (!(newtet = (t_tetro *)ft_memalloc(sizeof(*newtet))))
		return (NULL);
	return (listcoord(str, len, holdx, newtet));
}

/*
**  takes string and number of tetros generated from tetrovalid.c.
**  creates first tetronimo and places into linked list. populates
**	the rest of the list.
*/

t_tetro		*populate(char *str, int tetronum)
{
	t_tetro *firsttet;

	firsttet = makelist(&(*str), 21);
	while (--tetronum > 0)
	{
		str += 21;
		addtolist(makelist(&(*str), 21), firsttet);
	}
	return (firsttet);
}
