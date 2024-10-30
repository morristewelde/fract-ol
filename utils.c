/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:41:12 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/30 21:25:02 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

double	ft_atodb(char *s)
{
	int		sign;
	long	r;
	double	res;
	double	factor;

	sign = 1;
	r = 0;
	res = 0.0;
	factor = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + (*s++ - 48);
	if (*s == '.')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		factor /= 10;
		res = res + (*s++ - 48) * factor;
	}
	return ((res + r) * sign);
}

int	valid_float(char *s)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] == '.')
		{
			flag++;
			if (flag > 1)
				return (0);
		}
		else if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	if (ft_atodb(s) > 2.0 || ft_atodb(s) < -2.0)
		return (0);
	return (1);
}

//vector addition
t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.x_r = z1.x_r + z2.x_r;
	res.y_i = z1.y_i + z2.y_i;
	return (res);
}

//vector square x = (x^2 - y^2) y = (2xy)
t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.x_r = (z.x_r * z.x_r) - (z.y_i * z.y_i);
	res.y_i = 2 * z.x_r * z.y_i;
	return (res);
}

double	map_s(double old_n, double new_mn, double new_mx, double old_mx)
{
	return (((new_mx - new_mn) * old_n / (old_mx)) + new_mn);
}

void	putstr_fd(char *s, int fd)
{
	if (s == NULL || fd <  0)
		return ;
	if (*s)
	{
		write(fd, s, 1);
		putstr_fd(s + 1, 1);
	}
}
