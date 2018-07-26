
#include "fractol.h"

void free_fract(t_fract *data)
{
	free(data->mlx);
	free(data);
}

void    exit_fract(t_fract *data)
{
	mlx_destroy_image(data->mlx->mptr, data->mlx->img_ptr);
	mlx_clear_window(data->mlx->mptr, data->mlx->wptr);
	mlx_destroy_window(data->mlx->mptr, data->mlx->wptr);
	free_fract(data);
	exit(0);
}
void zoomk(t_fract *data)
{
    data->zoom *= 0.2;
    // data->itmax *= 2;
    // data->startx = x - data->z;
    // data->starty = y - data->z;
    // data->endx = x + data->z;
    // data->endy = y + data->z;
    // data->z -= 0.1;
  // }
  // mlx_destroy_image(data->mlx->mptr, data->mlx->img_ptr);
	mlx_clear_window(data->mlx->mptr, data->mlx->wptr);
	// data->mlx->data = (int *)mlx_get_data_addr(data->mlx->img_ptr, &data->mlx->bpp, &data->mlx->size_l, &data->mlx->endian);
  mandelbrot(data, 0, 0);
  		// mlx_do_sync(data->mlx->mptr);
  // mlx_put_image_to_window(data->mlx->mptr, data->mlx->wptr, data->mlx->img_ptr, 0, 0);
}
int keycode(int key, t_fract *data)
{
	if (key == 53)
		exit_fract(data);
	if (key == 78)
		zoomk(data);
	return (0);
}
