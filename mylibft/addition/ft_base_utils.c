/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:14:48 by skimura           #+#    #+#             */
/*   Updated: 2025/10/05 17:24:29 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_skip_whitespace(const char **p)
{
	while (ft_isspace(**p))
		(*p)++;
	return (0);
}

int	ft_parse_sign(const char **p)
{
	if (**p == '-')
	{
		(*p)++;
		return (-1);
	}
	if (**p == '+')
		(*p)++;
	return (1);
}

int	ft_parse_base(const char **p, int base)
{
	const char	*s = *p;

	if (base == 0)
	{
		if (*s == '0')
		{
			if (*(s + 1) == 'x' || *(s + 1) == 'X')
			{
				*p += 2;
				return (16);
			}
			else
			{
				*p += 1;
				return (8);
			}
		}
		return (10);
	}
	if (base == 16 && *s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
		*p += 2;
	return (base);
}

int	ft_isdigit_base(char c, int base)
{
	if (c >= '0' && c <= '9')
		return (c - '0' < base);
	if (c >= 'a' && c <= 'f')
		return (10 + c - 'a' < base);
	if (c >= 'A' && c <= 'F')
		return (10 + c - 'A' < base);
	return (0);
}

int	ft_getdigit_base(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (-1);
}
