/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:41:55 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/17 14:01:17 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "limits.h"

int	ft_isdigit(int d)
{
	return (d >= '0' && d <= '9');
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

long	ft_atol(char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	while (ft_is_space((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit((unsigned char)*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * (long)result);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*dest;
	size_t			total;

	total = -1;
	if (count != 0 && total / count < size)
		return (NULL);
	total = count * size;
	dest = malloc(total);
	if (dest == NULL)
		return (NULL);
	memset(dest, 0, total);
	return (dest);
}
