/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removedup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shagazi <shagazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:53:43 by shagazi           #+#    #+#             */
/*   Updated: 2018/05/11 15:15:19 by shagazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_removedup(char *str)
{
	int i;
	char *newstr;

	i = 0;
	newstr = ft_strnew(0);
	newstr[0] = str[i];
	while(str[i] != '\0')
	{
		if(ft_strchr(newstr, str[i]))
			i++;
		else
			newstr = ft_strncat(newstr, &str[i], 1);
 	}
	i = ft_strlen(newstr);
	newstr[i] = '\0';
	return(newstr);
}
