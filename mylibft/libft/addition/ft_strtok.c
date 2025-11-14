/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:09:11 by skimura           #+#    #+#             */
/*   Updated: 2025/11/07 17:26:46 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saveptr;

	return (ft_strtok_r(str, delim, &saveptr));
}
