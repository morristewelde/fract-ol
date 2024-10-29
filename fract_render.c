/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 03:57:09 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/29 22:01:01 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x *(img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	init_complex(t_complex *z, t_complex *c, t_data *data)
{
	if (ft_strncmp(data->name, "julia", 5) == 0)
	{
		c->x_r = data->julia_x;
		c->y_i = data->julia_y;
	}
	else
	{
		c->x_r = z->x_r;
		c->y_i = z->y_i;
	}
}

static int	get_color_pattern(unsigned int itr, unsigned int max_itr)
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

static void	handle_pixel(int x, int y, t_data *data)
{
	t_complex		z;
	t_complex		c;
	unsigned int	i;
	int				color;

	z.x_r = (map_s(x, -2, 2, WIDTH) * data->zoom) + data->shift_x;
	z.y_i = (map_s(y, 2, -2, HEIGHT) * data->zoom) + data->shift_y;
	init_complex(&z, &c, data);
	i = 0;
	while (i < data->iteration)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x_r * z.x_r) + (z.y_i * z.y_i) > data->escape_value)
		{
			color = get_color_pattern(i, data->iteration);
			my_pixel_put(x, y, &data->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &data->img, BLACK);
}

void	ft_render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			handle_pixel(x, y, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
}
