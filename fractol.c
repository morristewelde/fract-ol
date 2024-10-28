/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:29:17 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/28 18:15:12 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		m;
	int		j;

	m = ft_strncmp(av[1], "mandelbrot", 10);
	j = ft_strncmp(av[1], "julia", 5);
	if ((ac == 2 && m == 0) || (ac == 4 && j == 0))
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
