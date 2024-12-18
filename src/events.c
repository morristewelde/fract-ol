/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:29:17 by mtewelde          #+#    #+#             */
/*   Updated: 2024/11/01 22:48:29 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

/*int	mouse_handler(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == Button4)
		data->zoom *= 0.95;
	else if (button == Button5)
		data->zoom *= 1.05;
	ft_render(data);
	return (0);
}*/
int	mouse_handle(int button, int x, int y, t_data *data)
{
	double	mouse_fractal_x;
	double	mouse_fractal_y;
	double	center_x;
	double	center_y;
	double	zoom_factor;

	mouse_fractal_x = (map_s(x, -2, 2, WIDTH) * data->zoom) + data->shift_x;
	mouse_fractal_y = (map_s(y, 2, -2, HEIGHT) * data->zoom) + data->shift_y;
	center_x = (map_s(WIDTH / 2, -2, 2, WIDTH) * data->zoom) + data->shift_x;
	center_y = (map_s(HEIGHT / 2, -2, 2, HEIGHT) * data->zoom) + data->shift_y;
	if (button == 5)
		zoom_factor = 1.1;
	else if (button == 4)
		zoom_factor = 0.9;
	else
		return (0);
	data->zoom *= zoom_factor;
	data->shift_x += (mouse_fractal_x - center_x) * (1 - zoom_factor);
	data->shift_y += (mouse_fractal_y - center_y) * (1 - zoom_factor);
	ft_render(data);
	return (1);
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
	if (keysym == XK_Down || keysym == XK_s)
		data->shift_y += (0.2 * data->zoom);
	else if (keysym == XK_Up || keysym == XK_w)
		data->shift_y -= (0.2 * data->zoom);
	if (keysym == XK_Right || keysym == XK_d)
		data->shift_x -= (0.2 * data->zoom);
	else if (keysym == XK_Left || keysym == XK_a)
		data->shift_x += (0.2 * data->zoom);
	else if (keysym == XK_KP_Add)
		data->iteration += 5;
	else if (keysym == XK_KP_Subtract && data->iteration > 0)
		data->iteration -= 5;
	else if (keysym == XK_space)
		ft_reset(data);
	else if (keysym == XK_Escape)
		close_f(data);
	else if (keysym == XK_l)
		data->mouse_locked = !data->mouse_locked;
	ft_render(data);
	return (0);
}

int	julia_t(int x, int y, t_data *data)
{
	if (!ft_strcmp(data->name, "julia") && !data->mouse_locked)
	{
		data->julia_x = (map_s(x, -2, +2, WIDTH) * data->zoom);
		data->julia_y = (map_s(y, -2, +2, WIDTH) * data->zoom);
	}
	ft_render(data);
	return (0);
}
