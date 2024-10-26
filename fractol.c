/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:29:17 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/27 01:08:50 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atodb(char *s)
{
	int		sign;
	long	r;
	double	res;
	double	pow;

	sign = 1;
	r = 0;
	res = 0.0;
	pow = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		r = r * 10 + (*s - 48);
		s++;
	}
	if (*s == '.')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		pow /= 10;
		res = res + (*s++  - 48) * pow;
	}
	return ((res + r) * sign);
}

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

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x *(img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	ft_malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

// data->iteration = 240; beautful
void	data_init(t_data *data)
{
	data->escape_value = 4;
	data->iteration = 24;
	data->shift_x = 0;
	data->shift_y = 0;
	data->zoom = 1.0;
}

//linear interplation 
double	map_scale(double unscaled_num, double new_min,
					double new_max, double old_max)
{
	return (((new_max - new_min) * unscaled_num / (old_max)) + new_min);
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

static void	init_complex(t_complex *z, t_complex *c, t_data *data)
{	
	if (!ft_strncmp(data->name, "julia", 5))
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

static void	handle_pixel(int x, int y, t_data *data)
{
	t_complex	z;
	t_complex	c;
	int			color;
	int			i;

	z.x_r = (map_scale(x, -2, 2, WIDTH) * data->zoom) + data->shift_x;
	z.y_i = (map_scale(y, -2, 2, HEIGHT) * data->zoom) + data->shift_y;
	i = 0;
	init_complex(&z, &c, data);
	
	while (i < data->iteration)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x_r * z.x_r) + (z.y_i * z.y_i) > data->escape_value)
		{
			color = map_scale(i, BLACK, WHITE, data->iteration);
			my_pixel_put(x, y, &data->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &data->img, WHITE);
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

int	close_f(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	key_handle(int keysym, t_data *data)
{
	if (keysym == XK_Down)
		data->shift_y += (0.5 * data->zoom);
	else if (keysym == XK_Up)
		data->shift_y -= (0.5 * data->zoom);
	if (keysym == XK_Right)
		data->shift_x -= (0.5 * data->zoom);
	else if (keysym == XK_Left)
		data->shift_x += (0.5 * data->zoom);
	else if (keysym == 65451)
		data->iteration += 10;
	else if (keysym == 65453)
	{
		if ( data->iteration > 0)
			data->iteration -= 10;
	}	
	else if (keysym == XK_Escape)
		close_f(data);
	ft_render(data);
	return (1);
}

int	mouse_handle(int button, int x, int y, t_data *data)
{
	if (button == 5)
		data->zoom *= 1.1;
	else if (button == 4)
		data->zoom *= 0.9;
	ft_render(data);
	return (1);
}

int	julia_t(int x, int y, t_data *data)
{
	if (!ft_strncmp(data->name, "julia", 5))
	{
		data->julia_x = (map_scale(x, -2, +2, WIDTH) * data->zoom);
		data->julia_y = (map_scale(y, -2, +2, WIDTH) * data->zoom);
	}
	ft_render(data);
	return (0);
}

static void	event_init(t_data	*data)
{
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, key_handle, data);
	mlx_hook(data->mlx_win, ButtonPress, ButtonPressMask, mouse_handle, data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask, close_f, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask, julia_t, data);

}

void	fractal_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_malloc_error();
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, data->name);
	if (data->mlx_win == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		ft_malloc_error();
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (data->img.img_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		free(data->mlx_ptr);
		ft_malloc_error();
	}
	data->img.pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
	event_init(data);
	data_init(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)
		|| ac == 4 && !ft_strncmp(av[1], "julia", 5))
	{
		data.name = av[1];
		data.julia_x = 0;
		data.julia_y = 0;
		if (ac == 4)
		{
			data.julia_x = ft_atodb(av[2]);
			data.julia_y = ft_atodb(av[3]);
		}
		fractal_init(&data);
		ft_render(&data);
		mlx_loop(data.mlx_ptr);
	}
}
