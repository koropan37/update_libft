/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:56:07 by skimura           #+#    #+#             */
/*   Updated: 2025/10/05 19:57:45 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <limits.h>

static long	ft_parse_and_convert(t_strtol_ctx *ctx);
static int	ft_check_overflow(long result, int digit, int base, int sign);
static long	ft_handle_overflow(t_strtol_ctx *ctx);

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char		*original;
	const char		*p;
	t_strtol_ctx	ctx;

	if (!nptr)
	{
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}
	original = nptr;
	p = nptr;
	ft_skip_whitespace(&p);
	ctx.sign = ft_parse_sign(&p);
	ctx.base = ft_parse_base(&p, base);
	ctx.start = p;
	ctx.p = &p;
	ctx.endptr = endptr;
	if (p == ctx.start && endptr)
		*endptr = (char *)original;
	return (ft_parse_and_convert(&ctx));
}

static long	ft_parse_and_convert(t_strtol_ctx *ctx)
{
	long	result;
	int		digit;

	result = 0;
	while (ft_isdigit_base(**(ctx->p), ctx->base))
	{
		digit = ft_getdigit_base(**(ctx->p));
		if (ft_check_overflow(result, digit, ctx->base, ctx->sign))
			return (ft_handle_overflow(ctx));
		result = result * ctx->base + digit;
		(*(ctx->p))++;
	}
	if (*(ctx->p) != ctx->start && ctx->endptr)
		*(ctx->endptr) = (char *)*(ctx->p);
	if (*(ctx->p) == ctx->start)
		return (0);
	return (result * ctx->sign);
}

static int	ft_check_overflow(long result, int digit, int base, int sign)
{
	long			max_div;
	long			max_mod;
	unsigned long	abs_min;

	if (sign == 1)
	{
		max_div = LONG_MAX / base;
		max_mod = LONG_MAX % base;
	}
	else
	{
		abs_min = (unsigned long)LONG_MAX + 1UL;
		max_div = (long)(abs_min / base);
		max_mod = (long)(abs_min % base);
	}
	if (result > max_div || (result == max_div && digit > max_mod))
		return (1);
	return (0);
}

static long	ft_handle_overflow(t_strtol_ctx *ctx)
{
	errno = ERANGE;
	while (ft_isdigit_base(**(ctx->p), ctx->base))
		(*(ctx->p))++;
	if (ctx->endptr)
		*(ctx->endptr) = (char *)*(ctx->p);
	if (ctx->sign == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

// # include <stdio.h>
// # include <stdlib.h>

// static void	test_edge_cases_l(void);
// static void	test_boundary_values_l(void);

// int	main(void)
// {
// 	printf("=== ft_strtol エッジケーステスト ===\n");
// 	test_edge_cases_l();
// 	test_boundary_values_l();
// 	return (0);
// }

// static void	test_edge_cases_l(void)
// {
// 	char		*end;
// 	long		n;
// 	const char	*input;

// 	printf("\n--- エッジケーステスト ---\n");
// 	input = "";
// 	n = ft_strtol(input, &end, 10);
// 	printf("\"\" -> n = %ld, endptr points to start: ", n);
// 	if (end == input)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	n = ft_strtol("   ", &end, 10);
// 	printf("\"   \" -> n = %ld\n", n);
// 	n = ft_strtol("abc", &end, 10);
// 	printf("\"abc\" -> n = %ld\n", n);
// 	n = ft_strtol("   +", &end, 10);
// 	printf("\"   +\" -> n = %ld, rest = '%s'\n", n, end);
// 	n = ft_strtol("   -", &end, 10);
// 	printf("\"   -\" -> n = %ld, rest = '%s'\n", n, end);
// 	n = ft_strtol("+-42", &end, 10);
// 	printf("\"+-42\" -> n = %ld, rest = '%s'\n", n, end);
// 	n = ft_strtol("++42", &end, 10);
// 	printf("\"++42\" -> n = %ld, rest = '%s'\n", n, end);
// 	n = ft_strtol("0x", &end, 0);
// 	printf("\"0x\" -> n = %ld, rest = '%s'\n", n, end);
// 	n = ft_strtol("0", &end, 0);
// 	printf("\"0\" -> n = %ld, rest = '%s'\n", n, end);
// }

// static void	test_boundary_values_l(void)
// {
// 	char	*end;
// 	long	n;

// 	printf("\n--- 境界値テスト ---\n");
// 	printf("LONG_MAX = %ld\n", LONG_MAX);
// 	printf("LONG_MIN = %ld\n", LONG_MIN);
// 	errno = 0;
// 	n = ft_strtol("9223372036854775807", &end, 10);
// 	printf("LONG_MAX: n = %ld, errno = %d, valid = ", n, errno);
// 	if (n == LONG_MAX && errno == 0)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	errno = 0;
// 	n = ft_strtol("-9223372036854775808", &end, 10);
// 	printf("LONG_MIN: n = %ld, errno = %d, valid = ", n, errno);
// 	if (n == LONG_MIN && errno == 0)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	errno = 0;
// 	n = ft_strtol("9223372036854775808", &end, 10);
// 	printf("LONG_MAX+1: n = %ld, errno = %d, overflow = ", n, errno);
// 	if (n == LONG_MAX && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	errno = 0;
// 	n = ft_strtol("-9223372036854775809", &end, 10);
// 	printf("LONG_MIN-1: n = %ld, errno = %d, underflow = ", n, errno);
// 	if (n == LONG_MIN && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// }
