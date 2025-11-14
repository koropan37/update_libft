/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:48:26 by skimura           #+#    #+#             */
/*   Updated: 2025/11/13 18:33:53 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADDITION_H
# define ADDITION_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strpbrk(const char *s1, const char *s2);
size_t			ft_strcspn(const char *s, const char *reject);
size_t			ft_strspn(const char *s, const char *accept);
char			*ft_strrev(char *str);
int				ft_max(int *tab, unsigned int len);
int				ft_min(int *tab, unsigned int len);
void			ft_print_bits(unsigned char octet);
unsigned char	ft_swap_bits(unsigned char octet);
unsigned char	ft_reverse_bits(unsigned char octet);
int				ft_prime(int n);
unsigned int	ft_gcd(unsigned int a, unsigned int b);
unsigned int	ft_lcm(unsigned int a, unsigned int b);
int				ft_abs(int n);
double			ft_abs_double(double n);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strcat(char *dest, const char *src);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int				ft_isspace(char c);
long			ft_strtol(const char *nptr, char **endptr, int base);
long long		ft_strtoll(const char *nptr, char **endptr, int base);
int				ft_skip_whitespace(const char **p);
int				ft_parse_sign(const char **p);
int				ft_parse_base(const char **p, int base);
int				ft_isdigit_base(char c, int base);
int				ft_getdigit_base(char c);
int				ft_isblank(char c);
char			*ft_strstr(const char *haystack, const char *needle);
pid_t			ft_getpid(void);
char			*ft_strtok(char *str, const char *delim);
char			*ft_strtok_r(char *str, const char *delim, char **saveptr);
void			ft_replace_int(int *dst, int val);
void			ft_replace_char(char *dst, char val);
typedef struct s_strtol_ctx
{
	const char	**p;
	const char	*start;
	int			base;
	int			sign;
	char		**endptr;
}				t_strtol_ctx;

#endif
