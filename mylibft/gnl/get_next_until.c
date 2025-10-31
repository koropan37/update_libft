/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_until.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 21:43:00 by skimura           #+#    #+#             */
/*   Updated: 2025/10/20 22:20:48 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_get_until(const char *s, const char *nl);
char	*ft_find_substr(const char *s, const char *sep);
char	*ft_trim_until(char *s, const char *nl);
char	*ft_read_until(int fd, char *enter, const char *sep);

char	*get_next_until(int fd, const char *sep)
{
	static char	*files[FD_MAX];
	char		*block;

	if (fd < 0 || fd >= FD_MAX || !sep || sep[0] == '\0' || BUFFER_SIZE <= 0)
		return (NULL);
	files[fd] = ft_read_until(fd, files[fd], sep);
	if (!files[fd] || !*files[fd])
		return (free_and_null((void **)&files[fd]), NULL);
	block = ft_get_until(files[fd], sep);
	if (!block)
	{
		block = ft_get_newline(files[fd]);
		if (!block)
		{
			block = ft_substr(files[fd], 0, ft_strlen(files[fd]));
			free_and_null((void **)&files[fd]);
			return (block);
		}
		files[fd] = ft_trim_newline(files[fd]);
		return (block);
	}
	files[fd] = ft_trim_until(files[fd], sep);
	return (block);
}

char	*ft_get_until(const char *s, const char *nl)
{
	char	*pos;
	size_t	len;
	size_t	nl_len;

	if (!s || !nl)
		return (NULL);
	pos = ft_strnstr(s, nl, ft_strlen(s));
	if (!pos)
		return (NULL);
	nl_len = ft_strlen(nl);
	len = (size_t)(pos - s) + nl_len;
	return (ft_substr(s, 0, len));
}

char	*ft_find_substr(const char *s, const char *sep)
{
	size_t	sl;
	size_t	nl;
	size_t	i;

	if (!s || !sep)
		return (NULL);
	sl = ft_strlen(s);
	nl = ft_strlen(sep);
	if (nl == 0)
		return ((char *)s);
	if (nl > sl)
		return (NULL);
	i = 0;
	while (i + nl <= sl)
	{
		if (ft_strncmp(s + i, sep, nl) == 0)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_trim_until(char *s, const char *nl)
{
	char	*pos;
	size_t	nl_len;
	char	*rest;

	if (!s || !nl)
		return (NULL);
	pos = ft_strnstr(s, nl, ft_strlen(s));
	if (!pos)
	{
		free(s);
		return (NULL);
	}
	nl_len = ft_strlen(nl);
	if (!pos[nl_len])
		rest = ft_strdup("");
	else
		rest = ft_strdup(pos + nl_len);
	free(s);
	return (rest);
}

char	*ft_read_until(int fd, char *enter, const char *sep)
{
	ssize_t	bytes;
	char	*buffer;

	if (!sep)
		return (NULL);
	buffer = NULL;
	bytes = 1;
	if (enter && ft_find_substr(enter, sep))
		return (enter);
	while (!ft_find_substr(enter, sep) && bytes > 0)
	{
		bytes = ft_read_buf(fd, &buffer);
		if (bytes == -1)
			return (free(buffer), free(enter), NULL);
		if (bytes == 0)
			return (free(buffer), enter);
		enter = ft_strjoin_free(enter, buffer);
		free_and_null((void **)&buffer);
		if (!enter)
			return (NULL);
	}
	return (enter);
}

// #include <string.h>

// static void	write_file(const char *path, const char *data)
// {
// 	FILE	*f;

// 	f = fopen(path, "wb");
// 	if (!f)
// 	{
// 		perror("fopen");
// 		exit(1);
// 	}
// 	fwrite(data, 1, strlen(data), f);
// 	fclose(f);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*s;

// 	/* case1: simple */
// 	write_file("t1.txt", "helloENDworld");
// 	fd = open("t1.txt", O_RDONLY);
// 	s = get_next_until(fd, "END");
// 	printf("case1-1: [%s]\n", s ? s : "(NULL)");
// 	free(s);
// 	s = get_next_until(fd, "END");
// 	printf("case1-2: [%s]\n", s ? s : "(NULL)");
// 	free(s);
// 	close(fd);
// 	/* case2: sep at start */
// 	write_file("t2.txt", "SEPrest");
// 	fd = open("t2.txt", O_RDONLY);
// 	s = get_next_until(fd, "SEP");
// 	printf("case2-1: [%s]\n", s ? s : "(NULL)");
// 	free(s);
// 	s = get_next_until(fd, "SEP");
// 	printf("case2-2: [%s]\n", s ? s : "(NULL)");
// 	free(s);
// 	close(fd);
// 	/* case3: no sep */
// 	write_file("t3.txt", "nodelim");
// 	fd = open("t3.txt", O_RDONLY);
// 	s = get_next_until(fd, "XYZ");
// 	printf("case3: [%s]\n", s ? s : "(NULL)");
// 	free(s);
// 	close(fd);
// 	/* case4: multiple seps */
// 	write_file("t4.txt", "aSEP bSEP cSEP");
// 	fd = open("t4.txt", O_RDONLY);
// 	while ((s = get_next_until(fd, "SEP")) != NULL)
// 	{
// 		printf("case4 chunk: [%s]\n", s);
// 		free(s);
// 	}
// 	close(fd);
// 	/* case5: edge / buffer-boundary:
// 		build with -D BUFFER_SIZE=4
// 	return (0);
// }
