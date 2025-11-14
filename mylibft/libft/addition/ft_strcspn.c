/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:02:27 by skimura           #+#    #+#             */
/*   Updated: 2025/10/27 15:14:19 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;

	if (!s || !reject)
		return (0);
	i = 0;
	while (s[i] && !ft_strchr(reject, s[i]))
		i++;
	return (i);
}

// int	main(void)
// {
// 	const char	*s = "hallo , world";
// 	const char	*reject = "ol";

// 	printf("%zu\n", ft_strcspn(s, reject));
// 	return (0);
// }
