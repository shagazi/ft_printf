/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatstrchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shagazi <shagazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 13:46:23 by shagazi           #+#    #+#             */
/*   Updated: 2018/06/03 19:10:51 by shagazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	printchar(t_struct *fmt)
{
	if (FLGNEG(fmt))
	{
		if (fmt->spaces != NULL)
		{
			fmt->formatstr = ft_strappend(fmt->formatstr, fmt->spaces);
			ft_putchar(fmt->formatchar);
			ft_putstr(fmt->formatstr);
		}
		else
			ft_putchar(fmt->formatchar);
	}
	else
	{
		if (fmt->spaces != NULL || fmt->zeros != NULL)
		{
			fmt->formatstr = ft_strappend(fmt->spaces, fmt->formatstr);
			fmt->formatstr = ft_strappend(fmt->zeros, fmt->formatstr);
			ft_putstr(fmt->formatstr);
			ft_putchar(fmt->formatchar);
		}
		else
			ft_putchar(fmt->formatchar);
	}
}

void	printwidestr(t_struct *fmt)
{
	wchar_t		*p;
	int			i;

	p = fmt->formatwstr;
	i = 0;
	if (fmt->formatwstr == NULL)
	{
		ft_putstr("(null)");
		fmt->byte_len += 6;
	}
	else
	{
		while (*p)
		{
			ft_putchar((char)*p);
			p++;
			i++;
		}
		fmt->byte_len += (i);
	}
}

void	formatstr(t_struct *fmt)
{
	if (FLGNEG(fmt) && fmt->formatstr != NULL)
		fmt->formatstr = ft_strappend(fmt->formatstr, fmt->spaces);
	else if (fmt->spaces || fmt->zeros)
	{
		fmt->formatstr = ft_strappend(fmt->spaces, fmt->formatstr);
		fmt->formatstr = ft_strappend(fmt->zeros, fmt->formatstr);
	}
	if (fmt->format == 'S')
		printwidestr(fmt);
	else
		ft_putstr(fmt->formatstr);
}

void	strflag(t_struct *fmt)
{
	char *str;

	str = ft_strdup("(null)");
	if (fmt->formatstr == NULL && ft_strchr("s", fmt->format))
		fmt->formatstr = ft_strappend(fmt->formatstr, str);
	else
		free(str);
	if (fmt->presicion < FMTLEN(fmt) && fmt->presicionflag == 1)
		presicionstring(fmt, fmt->presicion);
	if (fmt->width > fmt->presicion || fmt->width > FMTLEN(fmt))
	{
		{
			if (ft_strchr(fmt->flags, '0'))
				flagzero(fmt, FMTLEN(fmt));
			else
				flagspace(fmt, FMTLEN(fmt));
		}
	}
}

void	charflag(t_struct *fmt)
{
	if (fmt->width > 1)
	{
		if (ft_strchr(fmt->flags, '0'))
			flagzero(fmt, 1);
		else
			flagspace(fmt, 1);
	}
	if (fmt->width < 0)
		flagspace(fmt, 1);
	printchar(fmt);
}
