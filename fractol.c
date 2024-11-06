/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:29:17 by mtewelde          #+#    #+#             */
/*   Updated: 2024/11/06 19:38:20 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	invalid_input(void)
{
	putstr_fd("Invalid Input\n", 2);
	putstr_fd("Please enter :\n", 2);
	putstr_fd("\"./fractol mandelbrot\"\n", 2);
	putstr_fd("\t or \"./fractol burningship\"\n", 2);
	putstr_fd("\t\t or  \"./fractol julia x y\"\n", 2);
	putstr_fd("x and y should ideally be between -2.0 and 2.0\"\n", 2);
	exit(1);
}

void	instructions(void)
{
	putstr_fd("To zoom in and out use scroll of the mouse\n", 1);
	putstr_fd("To close the windows use 'esc' key\n", 1);
	putstr_fd("\t or the close button on the opened window\n", 1);
	putstr_fd("To move use the arrows 'up' 'down' 'right' 'left'\n", 1);
	putstr_fd("\tor the keys 'w'(up) 's'(down) 'd'(right) 'a'(left)\n", 1);
	putstr_fd("To increase and decrease iteration\n", 1);
	putstr_fd("\t Use the keys '+' and '-'\n", 1);
	putstr_fd("Press 'space' to reset the fractol to the original set\n", 1);
	putstr_fd("\t This will increase and decrease image quality)\n", 1);
	putstr_fd("press 'l' to lock/unlock mouse hover during julia set\n", 1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2 && (!ft_strcmp(av[1], "mandelbrot")
			|| !ft_strcmp(av[1], "burningship")))
		data.name = av[1];
	else if (ac == 4 && !ft_strcmp(av[1], "julia"))
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
