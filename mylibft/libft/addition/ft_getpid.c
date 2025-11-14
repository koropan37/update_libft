/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:55:16 by skimura           #+#    #+#             */
/*   Updated: 2025/10/15 21:55:41 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/addition.h"

pid_t	ft_getpid(void)
{
	int		fd;
	ssize_t	bytes;
	char	buf[128];
	long	pid;
	size_t	i;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (bytes <= 0)
		return (-1);
	buf[bytes] = '\0';
	pid = 0;
	i = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		pid = pid * 10 + (buf[i] - '0');
		i++;
	}
	return (pid);
}
