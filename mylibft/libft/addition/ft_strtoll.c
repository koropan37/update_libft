/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:03:05 by skimura           #+#    #+#             */
/*   Updated: 2025/10/05 19:57:57 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <limits.h>

static long long	ft_parse_and_convert(t_strtol_ctx *ctx);
static int			ft_check_overflow(long long result, int digit, int base,
						int sign);
static long long	ft_handle_overflow(t_strtol_ctx *ctx);

long long	ft_strtoll(const char *nptr, char **endptr, int base)
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

static long long	ft_parse_and_convert(t_strtol_ctx *ctx)
{
	long long	result;
	int			digit;

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

static int	ft_check_overflow(long long result, int digit, int base, int sign)
{
	long long			max_div;
	long long			max_mod;
	unsigned long long	abs_min;

	if (sign == 1)
	{
		max_div = LLONG_MAX / base;
		max_mod = LLONG_MAX % base;
	}
	else
	{
		abs_min = (unsigned long long)LLONG_MAX + 1ULL;
		max_div = (long long)(abs_min / base);
		max_mod = (long long)(abs_min % base);
	}
	if (result > max_div || (result == max_div && digit > max_mod))
		return (1);
	return (0);
}

static long long	ft_handle_overflow(t_strtol_ctx *ctx)
{
	errno = ERANGE;
	while (ft_isdigit_base(**(ctx->p), ctx->base))
		(*(ctx->p))++;
	if (ctx->endptr)
		*(ctx->endptr) = (char *)*(ctx->p);
	if (ctx->sign == 1)
		return (LLONG_MAX);
	else
		return (LLONG_MIN);
}

// # include <stdio.h>
// # include <stdlib.h>

// static void			test_edge_cases_ll(void);
// static void			test_boundary_values_ll(void);

// int	main(void)
// {
// 	printf("=== ft_strtoll エッジケーステスト ===\n");
// 	test_edge_cases_ll();
// 	test_boundary_values_ll();
// 	return (0);
// }

// static void	test_edge_cases_ll(void)
// {
// 	char		*end;
// 	long long	n;
// 	const char	*input;

// 	printf("\n--- エッジケーステスト ---\n");
// 	// NULL入力
// 	n = ft_strtoll(NULL, &end, 10);
// 	printf("NULL -> n = %lld\n", n);
// 	// 空文字列
// 	input = "";
// 	n = ft_strtoll(input, &end, 10);
// 	printf("\"\" -> n = %lld, endptr points to start: ", n);
// 	if (end == input)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 空白のみ
// 	n = ft_strtoll("   ", &end, 10);
// 	printf("\"   \" -> n = %lld\n", n);
// 	// 数字なし
// 	n = ft_strtoll("abc", &end, 10);
// 	printf("\"abc\" -> n = %lld\n", n);
// 	// 符号のみ
// 	n = ft_strtoll("   +", &end, 10);
// 	printf("\"   +\" -> n = %lld, rest = '%s'\n", n, end);
// 	n = ft_strtoll("   -", &end, 10);
// 	printf("\"   -\" -> n = %lld, rest = '%s'\n", n, end);
// 	// 複数符号
// 	n = ft_strtoll("+-42", &end, 10);
// 	printf("\"+-42\" -> n = %lld, rest = '%s'\n", n, end);
// 	n = ft_strtoll("--42", &end, 10);
// 	printf("\"--42\" -> n = %lld, rest = '%s'\n", n, end);
// 	// 16進数エッジケース
// 	n = ft_strtoll("0x", &end, 16);
// 	printf("\"0x\" (base 16): n = %lld, rest = '%s'\n", n, end);
// 	n = ft_strtoll("0xG", &end, 16);
// 	printf("\"0xG\": n = %lld, rest = '%s'\n", n, end);
// 	// 8進数エッジケース
// 	n = ft_strtoll("08", &end, 0);
// 	printf("\"08\" (invalid octal): n = %lld, rest = '%s'\n", n, end);
// 	// 先頭ゼロのみ
// 	n = ft_strtoll("000", &end, 0);
// 	printf("\"000\": n = %lld, rest = '%s'\n", n, end);
// }

// static void	test_boundary_values_ll(void)
// {
// 	char		*end;
// 	long long	n;

// 	printf("\n--- 境界値テスト ---\n");
// 	printf("LLONG_MAX = %lld\n", LLONG_MAX);
// 	printf("LLONG_MIN = %lld\n", LLONG_MIN);
// 	// 正確な最大値（有効）
// 	errno = 0;
// 	n = ft_strtoll("9223372036854775807", &end, 10);
// 	printf("LLONG_MAX: n = %lld, errno = %d, valid = ", n, errno);
// 	if (n == LLONG_MAX && errno == 0)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 正確な最小値（有効）
// 	errno = 0;
// 	n = ft_strtoll("-9223372036854775808", &end, 10);
// 	printf("LLONG_MIN: n = %lld, errno = %d, valid = ", n, errno);
// 	if (n == LLONG_MIN && errno == 0)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 最大値+1（無効・オーバーフロー）
// 	errno = 0;
// 	n = ft_strtoll("9223372036854775808", &end, 10);
// 	printf("LLONG_MAX+1: n = %lld, errno = %d, overflow = ", n, errno);
// 	if (n == LLONG_MAX && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 最小値-1（無効・アンダーフロー）
// 	errno = 0;
// 	n = ft_strtoll("-9223372036854775809", &end, 10);
// 	printf("LLONG_MIN-1: n = %lld, errno = %d, underflow = ", n, errno);
// 	if (n == LLONG_MIN && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 16進数での最大値（有効）
// 	errno = 0;
// 	n = ft_strtoll("0x7FFFFFFFFFFFFFFF", &end, 0);
// 	printf("Hex LLONG_MAX: n = %lld, errno = %d, valid = ", n, errno);
// 	if (n == LLONG_MAX && errno == 0)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 16進数での最大値+1（無効）
// 	errno = 0;
// 	n = ft_strtoll("0x8000000000000000", &end, 0);
// 	printf("Hex LLONG_MAX+1: n = %lld, errno = %d, overflow = ", n, errno);
// 	if (n == LLONG_MAX && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 負の16進数での最小値（有効）
// 	errno = 0;
// 	n = ft_strtoll("-0x8000000000000000", &end, 0);
// 	printf("Hex LLONG_MIN: n = %lld, errno = %d, valid = ", n, errno);
// 	if (n == LLONG_MIN && errno == 0)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 巨大なオーバーフロー
// 	errno = 0;
// 	n = ft_strtoll("99999999999999999999999999999999", &end, 10);
// 	printf("Big overflow: n = %lld, errno = %d, overflow = ", n, errno);
// 	if (n == LLONG_MAX && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	errno = 0;
// 	n = ft_strtoll("-99999999999999999999999999999999", &end, 10);
// 	printf("Big underflow: n = %lld, errno = %d, underflow = ", n, errno);
// 	if (n == LLONG_MIN && errno == ERANGE)
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	// 数字の途中で停止する場合
// 	errno = 0;
// 	n = ft_strtoll("9223372036854775807abc", &end, 10);
// 	printf("LLONG_MAX+suffix: n = %lld, errno = %d, rest = '%s'\n", n, errno,
// 		end);
// }
