/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:38:11 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/27 00:31:56 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define WIDTH	800
#define HEIGHT	800

#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)


// Psychedelic colors
#define MAGENTA_BURST   0xFF00FF  // A vibrant magenta
#define LIME_SHOCK      0xCCFF00  // A blinding lime
#define NEON_ORANGE     0xFF6600  // A blazing neon orange
#define PSYCHEDELIC_PURPLE 0x660066  // A deep purple
#define AQUA_DREAM      0x33CCCC  // A bright turquoise
#define HOT_PINK        0xFF66B2  // As the name suggests!
#define ELECTRIC_BLUE   0x0066FF  // A radiant blue
#define LAVA_RED        0xFF3300  // A bright, molten red

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int 	bpp;
	int		endian;
	int		line_len;
} t_img;

typedef struct s_complex 
{
	double	x_r;
	double	y_i;
} 				t_complex;

typedef struct s_data
{
	char	*name;
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	img;
	double	escape_value;
	unsigned int		iteration;
	double shift_x;
	double shift_y;
	double zoom;
	double julia_x;
	double julia_y;
} t_data;


int	ft_strncmp(char *s1, char *s2, int n);
void	data_init(t_data *data);
double map_scale(double unscaled_num, double new_min, double new_max, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
void	ft_render(t_data *data);
void	fractal_init(t_data *data);



#endif