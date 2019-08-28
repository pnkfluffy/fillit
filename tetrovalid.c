/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrovalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelee <lelee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 12:20:31 by jfelty            #+#    #+#             */
/*   Updated: 2019/08/24 16:31:04 by lelee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		validchar(char c)
{
	if (c == '\n' || c == '#' || c == '.')
		return (1);
	return (0);
}

/*
**	checks that only valid characters are sent through the input.
**	also checks that the field is of valid size with correct
**	tetronimo separators. returns the number of tetronimos sent
**	through. or 0 if invalid field.
*/

int		validfield(char *input)
{
	int i;
	int tetronum;

	i = -1;
	tetronum = 0;
	while (input[++i])
	{
		if (!(validchar(input[i])))
			return (0);
		if (input[i] == '\n' && ((i + 1 - tetronum) % 5 != 0))
			return (0);
		if ((i + 1 - tetronum) % 20 == 0)
		{
			if (input[i + 1])
			{
				tetronum++;
				i++;
			}
			else
				return (tetronum + 1);
		}
	}
	return (0);
}

/*
**	returns the number of connecting sides for each tetronimo.
*/

int		connectcheck(const char *i, int n)
{
	int touching;

	touching = 0;
	if (n < 1)
		return ((*(i + 1) == '#') + (*(i + 5) == '#'));
	if (n < 4)
		return ((*(i + 1) == '#') + (*(i - 1) == '#') + (*(i + 5) == '#'));
	if (ft_numcharstrn(&i[-5], '\n', 5) == 2 && *(i + 5) == '#')
		touching++;
	else if (ft_numcharstrn(&i[0], '\n', 5) == 2 && *(i - 5) == '#')
	{
		touching++;
	}
	else
	{
		if (*(i + 5) == '#')
			touching++;
		if (*(i - 5) == '#')
			touching++;
	}
	if (*(i + 1) == '#')
		touching++;
	if (*(i - 1) == '#')
		touching++;
	return (touching);
}

/*
**	checks that each tetronimo is valid. first passes string into
**	ft_numcharstrn, which thecks that each segment has 4 '#'. than while
**	we do not encounter two new line characters in a row, the function
**	checks that each block has a total of six connecting sides. failing
** any of these checks returns 0.
*/

int		tetrochecker(const char *str, int tetronum)
{
	int i;
	int	sides;

	i = 0;
	sides = 0;
	while (--tetronum >= 0 && str[i])
	{
		if (ft_numcharstrn(&str[i], '#', 20) != 4)
			return (0);
		while ((str[i] != '\n' || str[i + 1] != '\n') && str[i])
		{
			if (str[i] == '#')
				sides += connectcheck(&str[i], i);
			i++;
		}
		if (sides < 6)
			return (0);
		sides = 0;
		i += 2;
	}
	return (1);
}

int		mastercheck(char *tetro)
{
	int tetronum;

	if (!(tetronum = validfield(tetro)))
		return (-1);
	if (!(tetrochecker(tetro, tetronum)))
		return (-1);
	return (tetronum);
}
