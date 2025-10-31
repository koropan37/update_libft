/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:55:11 by skimura           #+#    #+#             */
/*   Updated: 2025/10/27 15:13:52 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	if (!s || !accept)
		return (0);
	i = 0;
	while (s[i] && ft_strchr(accept, s[i]))
		i++;
	return (i);
}

// int	main(void)
// {
// 	const char	*s = "hello";
// 	const char	*accept = "jfkhpell";

// 	printf("%zu\n", ft_strspn(s, accept));
// }
