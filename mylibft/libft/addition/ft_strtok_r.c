/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:18:50 by skimura           #+#    #+#             */
/*   Updated: 2025/11/07 17:26:35 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/addition.h"

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*tmpptr;

	if (!str)
		str = *saveptr;
	str += ft_strspn(str, delim);
	if (!*str)
	{
		*saveptr = str;
		return (NULL);
	}
	tmpptr = str + ft_strcspn(str, delim);
	if (*tmpptr)
		*tmpptr++ = '\0';
	*saveptr = tmpptr;
	return (str);
}
