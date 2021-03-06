/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shagazi <shagazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 23:45:47 by shagazi           #+#    #+#             */
/*   Updated: 2018/06/01 17:41:09 by shagazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*signedcast(va_list *arg, t_struct *fmt)
{
	int				m;
	long long int	n;

	m = fmt->modifier;
	if (m == MOD_HH)
		n = (signed char)va_arg(*arg, int);
	else if (m == MOD_LL)
		n = (long long int)va_arg(*arg, long long int);
	else if (m == MOD_H)
		n = (short int)va_arg(*arg, int);
	else if (m == MOD_L || fmt->format == 'D')
		n = (long int)va_arg(*arg, long int);
	else if (m == MOD_J)
		n = va_arg(*arg, intmax_t);
	else if (m == MOD_Z)
		n = va_arg(*arg, size_t);
	else
		n = (int)va_arg(*arg, int);
	return (convert_int_toalpha((void *)&n, fmt));
}

char	*unsignedcast(va_list *arg, t_struct *fmt)
{
	unsigned long long int n;

	if (fmt->format == 'o' || fmt->format == 'O')
		fmt->basenumber = OCT;
	else if (fmt->format == 'x')
		fmt->basenumber = HEX;
	else if (fmt->format == 'X')
		fmt->basenumber = HEXX;
	if (fmt->modifier == MOD_L || fmt->format == 'U' || fmt->format == 'O')
		n = (unsigned long int)va_arg(*arg, unsigned long int);
	else if (fmt->modifier == MOD_LL)
		n = (unsigned long long int)va_arg(*arg, unsigned long long int);
	else if (fmt->modifier == MOD_HH)
		n = (unsigned char)va_arg(*arg, int);
	else if (fmt->modifier == MOD_H)
		n = (unsigned short)va_arg(*arg, unsigned int);
	else if (fmt->modifier == MOD_J)
		n = va_arg(*arg, uintmax_t);
	else if (fmt->modifier == MOD_Z)
		n = va_arg(*arg, ssize_t);
	else
		n = (unsigned int)va_arg(*arg, unsigned int);
	return (convert_int_toalpha((void *)&n, fmt));
}

void	wchar_check(va_list *arg, t_struct *fmt)
{
	wchar_t p;

	if (fmt->format == 'C')
	{
		p = (wchar_t)va_arg(*arg, wchar_t);
		fmt->formatchar = p;
	}
	if (fmt->format == 'S')
	{
		fmt->formatwstr = va_arg(*arg, wchar_t*);
	}
}

void	char_check(t_struct *fmt, va_list *arg)
{
	if (fmt->format == 'c')
		fmt->formatchar = (char)va_arg(*arg, int);
	if (fmt->format == 's')
		fmt->formatstr = ft_strdup(va_arg(*arg, char *));
}

void	formatcheck(va_list *arg, t_struct *fmt)
{
	char f;
	void *ptr;

	f = fmt->format;
	if (ft_strchr("DU", f))
		fmt->modifier = MOD_L;
	if (ft_strchr("Ddi", f))
		castint(fmt, arg);
	else if (ft_strchr("oOuUxX", f))
		fmt->formatstr = (char *)unsignedcast(arg, fmt);
	else if (ft_strchr("cs", f))
		char_check(fmt, arg);
	else if (ft_strchr("CS", f))
		wchar_check(arg, fmt);
	else if (fmt->format == 'p')
	{
		ptr = va_arg(*arg, void *);
		fmt->formatstr = convert_int_toalpha(ptr, fmt);
	}
	else if (f == '%')
		fmt->formatchar = '%';
}
