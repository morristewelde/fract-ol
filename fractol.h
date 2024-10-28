/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:38:11 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/28 17:48:50 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIDTH	500
# define HEIGHT	500

# define BLACK       0x000000
# define WHITE       0xFFFFFF  
# define RED         0xFF0000
# define GREEN       0x00FF00
# define BLUE        0x0000FF

# define MAGENTA_BURST   0xFF00FF
# define LIME_SHOCK      0xCCFF00
# define NEON_ORANGE     0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM      0x33CCCC
# define HOT_PINK        0xFF66B2
# define ELECTRIC_BLUE   0x0066FF
# define LAVA_RED        0xFF3300

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_complex
{
	double	x_r;
	double	y_i;
}	t_complex;

typedef struct s_data
{
	char			*name;
	void			*mlx_ptr;
	void			*mlx_win;
	t_img			img;
	double			escape_value;
	unsigned int	iteration;
	double			shift_x;
	double			shift_y;
	double			zoom;
	double			julia_x;
	double			julia_y;
}	t_data;

double		map_s(double old_n, double new_mn, double new_mx, double old_mx);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
void		ft_render(t_data *data);

// initializing the fractal
void		fractal_init(t_data *data);
void		data_init(t_data *data);

//events mouse, lose, key, ad initiaizin evets
int			julia_t(int x, int y, t_data *data);
int			key_handle(int keysym, t_data *data);
int			close_f(t_data *data);
int			mouse_handle(int button, int x, int y, t_data *data);

// utils for calulating and coverting double
double		ft_atodb(char *s);
int			ft_strncmp(char *s1, char *s2, int n);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

#endif
