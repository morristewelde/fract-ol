/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:41:12 by mtewelde          #+#    #+#             */
/*   Updated: 2024/11/01 22:46:47 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s2[i] && !s1[i])
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

//	recommened to add
//	if (ft_atodb(s) > 2.0 || ft_atodb(s) < -2.0)
//		return (0);
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
	return (1);
}

void	putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	if (*s)
	{
		write(fd, s, 1);
		putstr_fd(s + 1, 1);
	}
}

int	color_pattern(unsigned int itr, unsigned int max_itr)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;
	int		res;

	ratio = (double)itr / max_itr;
	red = (int)(9 * (1 - ratio) * ratio * ratio * ratio * 255);
	green = (int)(15 * (1 - ratio) * (1 - ratio) * ratio * ratio * 255);
	blue = (int)(8.5 * (1 - ratio) * (1 - ratio) * (1 - ratio) * ratio * 255);
	res = (red << 16) | (green << 8) | (blue);
	return (res);
}
