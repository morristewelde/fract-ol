/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:41:12 by mtewelde          #+#    #+#             */
/*   Updated: 2024/11/01 22:47:02 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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

void	ft_reset(t_data *data)
{
	data->escape_value = 4;
	data->iteration = 15;
	data->shift_x = 0;
	data->shift_y = 0;
	data->zoom = 1.0;
	if (!ft_strcmp(data->name, "julia"))
	{
		data->julia_x = data->initial_julia_x;
		data->julia_y = data->initial_julia_y;
	}
	ft_render(data);
}

void	ft_absolute(t_complex *nb)
{
	if (nb->x_r < 0)
		nb->x_r *= -1;
	if (nb->y_i < 0)
		nb->y_i *= -1;
}
