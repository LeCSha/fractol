
#include "fractol.h"

void zoom(t_fract *data, int x, int y)
{
  double x_r = x / data->zoom + data->startx;
  double y_r = y / data->zoom + data->starty;
  data->zoom *= 2;
  data->itmax *= 200;
  data->imgx *= 2;
  data->imgy *= 2;
  data->startx = x_r - data->imgx / data->zoom / 2;
  data->starty = y_r - data->imgy / data->zoom / 2;
  // data->endx = x + data->z;
  // data->endy = y + data->z;
  // data->z -= 0.1;
  // mlx_destroy_image(data->mlx->mptr, data->mlx->img_ptr);
	mlx_clear_window(data->mlx->mptr, data->mlx->wptr);
	// data->mlx->data = (int *)mlx_get_data_addr(data->mlx->img_ptr, &data->mlx->bpp, &data->mlx->size_l, &data->mlx->endian);
  mandelbrot(data, 0, 0);
  		// mlx_do_sync(data->mlx->mptr);
  // mlx_put_image_to_window(data->mlx->mptr, data->mlx->wptr, data->mlx->img_ptr, 0, 0);
}

int mousecode(int button, int x, int y, t_fract *data)
{
  if (button == 1 || button == 5)
    zoom(data, x, y);
  return (0);
}
