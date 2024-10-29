#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>

typedef struct s_img
{
	void	*ptr;
	char	*pxl_ptr;
	int		len;
	int		bpp;
	int		endian;
} t_img;

typedef struct s_data 
{
	char	*name;
	void	*ptr;
	void	*win;
	int		iteration;
	t_img	img;
} t_data;

int ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

/*static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int offset;
	offset = (y * img->len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pxl_ptr + offset) = color;
}*/

// static void	handle_pixel(int x, int y, t_data *data)
// {
	
// }

void	ft_render(t_data *data, int color)
{
	int x = 500;
	int y = 500;

	while (y >= 0)
	{
		x = y;
		while(x > 500 - y)
		{
			mlx_pixel_put(data->ptr, data->win, x, y, color);
			x--;
		}
		y--;
	}
}


// int (*f)(int button, int x, int y, void *param)
int	mouse_handle(int button, int x, int y, t_data *data)
{
	if (button == 1)
		printf("%d\n", button);
	else if (button == 2)
		printf("scroll has been pressed\n");
	else if (button == 3)
		printf("right click\n");
	return (1);
}

int	key_handle(int keysym, t_data *data)
{
	if (keysym == XK_r)
		ft_render(data, 0xff0000);
	else if (keysym == XK_g)
		ft_render(data, 0x00ff00);
	else if (keysym == XK_b)
		ft_render(data, 0x0000ff);
	else if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->ptr, data->win);
		mlx_destroy_display(data->ptr);
		free(data->ptr);
		exit(1);
	}
	return (1);	
}

void	ft_events(t_data *data)
{
	mlx_hook(data->win, ButtonPress, ButtonPressMask, mouse_handle, &data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handle, data);
}

int	main(int ac, char **av)
{
	int 	i;
	t_data	data;

	i = ft_strncmp(av[1], "mandelbrot", 10);
	if (ac == 2 && !i)
	{
		data.name = av[1];
		data.iteration = 20;
		data.ptr = mlx_init();
		data.win = mlx_new_window(data.ptr, 500, 500, "morris");
		data.img.ptr = mlx_new_image(data.ptr, 500, 500);
		data.img.pxl_ptr = mlx_get_data_addr(&data.img.ptr, &data.img.bpp, &data.img.len, &data.img.endian);
		ft_events(&data);
		mlx_loop(data.ptr);
	}
	return (0);
}
