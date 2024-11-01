/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 03:57:09 by mtewelde          #+#    #+#             */
/*   Updated: 2024/11/01 20:11:39 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

void	data_init(t_data *data)
{
	data->escape_value = 4;
	data->iteration = 15;
	data->shift_x = 0;
	data->shift_y = 0;
	data->zoom = 1.0;
	data->mouse_locked = 0;
	if (!ft_strncmp(data->name, "julia", 5))
	{
		data->initial_julia_x = data->julia_x;
		data->initial_julia_y = data->julia_y;
	}
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
