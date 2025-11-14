/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 22:09:25 by skimura           #+#    #+#             */
/*   Updated: 2025/11/06 22:12:16 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_replace_int(int *dst, int val)
{
	if (dst)
		*dst = val;
}

void	ft_replace_char(char *dst, char val)
{
	if (dst)
		*dst = val;
}
