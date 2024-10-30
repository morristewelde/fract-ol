/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:29:17 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/30 20:44:39 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	invalid_input(void)
{
	printf("Invalid Input\n");
	printf("please enter : \n");
	printf("\"./fractol mandelbrot or ./fractol julia x y\"\n");
	printf("x and y should be between -2.0 and 2.0\n");
	exit(EXIT_FAILURE);
}

void	instructions(void)
{
	printf("to zoom in and out use scroll of the mouse\n");
	printf("to move use the arrows or the keys 'w' 'a' 's' 'd': \n");
	printf("to increase and decrease iteration use the keys '+' and '-'\n");
}

int	main(int ac, char **av)
{
	t_data	data;
	int		m;
	int		j;

	m = ft_strncmp(av[1], "mandelbrot", 10);
	j = ft_strncmp(av[1], "julia", 5);
	if (ac == 2 && m == 0)
		data.name = av[1];
	else if (ac == 4 && j == 0)
	{
		if (!valid_float(av[2]) || !valid_float(av[3]))
			invalid_input();
		data.name = av[1];
		data.julia_x = ft_atodb(av[2]);
		data.julia_y = ft_atodb(av[3]);
	}
	else
		invalid_input();
	fractal_init(&data);
	ft_render(&data);
	instructions();
	mlx_loop(data.mlx_ptr);
	return (0);
}
