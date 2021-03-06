/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shagazi <shagazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:15:06 by shagazi           #+#    #+#             */
/*   Updated: 2018/06/02 00:11:46 by shagazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	flagspace(t_struct *fmt, int strlength)
{
	int		i;
	int		s;
	char	*spaces;

	i = fmt->width;
	s = 0;
	if (i < 0)
		i *= -1;
	if (i > strlength)
	{
		spaces = ft_strnew(i - strlength);
		if (ft_strchr(fmt->flags, '+') || (!(ft_strcmp(fmt->sign, "-"))))
			i--;
		while (i > strlength)
		{
			spaces[s] = ' ';
			s++;
			i--;
		}
		fmt->spaces = ft_strappend(fmt->spaces, spaces);
	}
}

void	flagzero(t_struct *fmt, int strlength)
{
	int		i;
	int		z;
	char	*zeros;

	i = fmt->width;
	z = 0;
	if (i > strlength)
	{
		zeros = ft_strnew(i - strlength);
		if (ft_strchr(fmt->flags, '+') || (!(ft_strcmp(fmt->sign, "-"))))
			i--;
		if (ft_strchr(fmt->flags, ' '))
			i--;
		while (i > strlength)
		{
			zeros[z] = '0';
			z++;
			i--;
		}
		fmt->zeros = ft_strappend(fmt->zeros, zeros);
	}
}

void	flaghex(t_struct *fmt)
{
	if (fmt->format == 'o')
		fmt->hex = ft_strdup("0");
	if (fmt->format == 'O')
		fmt->hex = ft_strdup("0");
	if ((fmt->format == 'x' && ft_strcmp(fmt->formatstr, "0")) ||
		fmt->format == 'p')
		fmt->hex = ft_strdup("0x");
	if (fmt->format == 'X' && ft_strcmp(fmt->formatstr, "0"))
		fmt->hex = ft_strdup("0X");
}

void	set_args(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

void	flagundef(t_struct *fmt)
{
	int		i;
	int		j;
	char	*newstr;
	char	*flagstr;

	set_args(&i, &j);
	if (ft_strlen(fmt->flags) >= 1)
	{
		newstr = ft_strnew(5);
		flagstr = ft_strdup(fmt->flags);
		free(fmt->flags);
		while (flagstr[i] != '\0')
		{
			if (!((flagstr[i] == ' ' && ft_strchr(flagstr, ' ')
				&& ft_strchr(flagstr, '+')) || (flagstr[i] == '0' &&
				ft_strchr(flagstr, '0') && ft_strchr(flagstr, '-')) ||
				(flagstr[i] == ' ' && (fmt->width > 0 || (!FLGMINUS(fmt))
				|| ft_strchr("uUoOxXp", fmt->format)) &&
				(!ft_strchr("di", fmt->format)))))
				newstr[j++] = flagstr[i];
			i++;
		}
		free(flagstr);
		fmt->flags = newstr;
	}
}
