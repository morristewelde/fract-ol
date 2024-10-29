/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:29:17 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/29 22:31:39 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_handle(int button, int x, int y, t_data *data)
{
	double	mouse_fractal_x;
	double	mouse_fractal_y;
	double	zoom_factor;

	// Map the current mouse position to the fractal coordinates
	mouse_fractal_x = (map_s(x, -2, 2, WIDTH) * data->zoom);
	mouse_fractal_y = (map_s(y, -2, 2, HEIGHT) * data->zoom);

	// Determine the zoom factor based on the mouse scroll (button 5 to zoom in, button 4 to zoom out)
	if (button == 5) // Zoom in
		zoom_factor = 1.1;
	else if (button == 4) // Zoom out
		zoom_factor = 0.9;
	else
		return (0); // Return early if no zoom buttons are pressed

	// Update zoom level
	data->zoom *= zoom_factor;

	// Adjust shift to re-center the zoom around the mouse position
	data->shift_x = mouse_fractal_x - (map_s(x, -2, 2, WIDTH) * data->zoom);
	data->shift_y = mouse_fractal_y - (map_s(y, -2, 2, HEIGHT) * data->zoom);

	// Redraw the fractal
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
		data->shift_y -= (0.5 * data->zoom);
	else if (keysym == XK_Up || keysym == XK_w)
		data->shift_y += (0.5 * data->zoom);
	if (keysym == XK_Right || keysym == XK_d)
		data->shift_x -= (0.5 * data->zoom);
	else if (keysym == XK_Left || keysym == XK_a)
		data->shift_x += (0.5 * data->zoom);
	else if (keysym == XK_KP_Add)
		data->iteration += 5;
	else if (keysym == XK_KP_Subtract && data->iteration > 0)
		data->iteration -= 5;
	else if (keysym == XK_Escape)
		close_f(data);
	ft_render(data);
	return (1);
}

int	julia_t(int x, int y, t_data *data)
{
	if (!ft_strncmp(data->name, "julia", 5))
	{
		data->julia_x = (map_s(x, -2, +2, WIDTH) * data->zoom);
		data->julia_y = (map_s(y, -2, +2, WIDTH) * data->zoom);
	}
	ft_render(data);
	return (0);
}
