/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:38:11 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/31 21:23:25 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIDTH	800
# define HEIGHT	800

# define BLACK 0x000000
# define WHITE 0xFFFFFF

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
	int				current_color;
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
double		ft_abs_dbl(double nb);
int			ft_strncmp(char *s1, char *s2, int n);
int			valid_float(char *s);
int			get_color_pattern(unsigned int itr, unsigned int max_itr);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
void		putstr_fd(char *s, int fd);

#endif
