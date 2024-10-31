/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:41:12 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/31 23:03:17 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	get_color_pattern(unsigned int itr, unsigned int max_itr)
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

void	ft_reset(t_data *data)
{
	data->escape_value = 4;
	data->iteration = 15;
	data->shift_x = 0;
	data->shift_y = 0;
	data->zoom = 1.0;
	if (!ft_strncmp(data->name, "julia", 5))
	{
		data->julia_x = data->initial_julia_x;
		data->julia_y = data->initial_julia_y;
	}
	ft_render(data);
}
