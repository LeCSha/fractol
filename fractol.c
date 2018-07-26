#include "fractol.h"

void print_error(int nb, t_fract *data)
{
  if (nb == 1)
    ft_putstr("Problem with allocation memory\n");
  else if (nb == 2)
    ft_putstr("Map not valid\n");
  else if (nb == 3)
    ft_putstr("Problem reading file/allocation failed\n");
  else if (nb == 4)
    ft_putstr("Map size not valid/no value\n");
  else if (nb == 5)
    data = NULL;
    // fdf_usage();
  exit(0);
}

void init_mlx(t_fract *data)
{
  if (!(data->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
    print_error(1, data);
  data->mlx->mptr = mlx_init();
  data->mlx->wptr = mlx_new_window(data->mlx->mptr, WIDTH, HEIGHT, "Fract'ol");
  data->mlx->img_ptr = mlx_new_image(data->mlx->mptr, WIDTH, HEIGHT);
  data->mlx->data = (int *)mlx_get_data_addr(data->mlx->img_ptr, &data->mlx->bpp, &data->mlx->size_l, &data->mlx->endian);
}

void init_mandel(t_fract *data)
{
  data->itmax = 50;
  data->z = 1000;
  data->zoom = 800;
  data->startx = -2;
  data->endx = 2;
  data->starty = -2;
  data->endy = 2;
  data->imgx = WIDTH;
  data->imgy = HEIGHT;
}

void draw_fractal(t_fract *data, int x, int y, int color)
{
  data->mlx->data[y * WIDTH + x] = color;
}

void mandelbrot(t_fract *data, int x, int y)
{
  double i;
  double tmp;
  double tmp2;

  while (y < data->imgy)
  {
    while (x < data->imgx)
    {
      data->c_r = (x * (data->endx - data->startx)) / data->zoom + data->starty;
      data->c_i = (y * (data->starty - data->endy)) / data->zoom + data->endy;
      data->z_r = 0;
      data->z_i = 0;
      i = 0;
      while (data->z_r * data->z_r + data->z_i * data->z_i < 4 && i < data->itmax)
      {
        tmp = data->z_r;
        tmp2 = data->z_i;
        data->z_r = tmp * tmp - tmp2 * tmp2 + data->c_r;
        data->z_i = 2 * tmp * tmp2 + data->c_i;
        i++;
      }
      if (i == data->itmax)
        mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, 0x000000);
        // draw_fractal(data, x, y, 0xFFFFFF);
      else
      {
        // i = i - log(log(sqrt(data->z_r * data->z_r + data->z_i * data->z_r))) / log(2);
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, i * (0xFF0000 / data->itmax) / 50);
        i = i + 1 - log(log(data->z_r * data->z_r + data->z_i * data->z_r)) / 2;
        mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, i * 0x84742d / data->itmax);
        // i = i - log(log(sqrt(data->z_r * data->z_r + data->z_i * data->z_r))) / log(2);
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, i * 3 * 256 / data->itmax);
      }
      x++;
    }
    x = 0;
    y++;
  }
}

int main(void)
{
  t_fract *data;

  if (!(data = (t_fract *)malloc(sizeof(t_fract))))
    print_error(1, data);
  init_mlx(data);
  // if (ac < 1)
  //   return (0);
  // if (ft_strncmp(av[1], "mandel", 6) == 0)
  init_mandel(data);
  mandelbrot(data, 0, 0);
  // mlx_put_image_to_window(data->mlx->mptr, data->mlx->wptr, data->mlx->img_ptr, 0, 0);
  mlx_key_hook(data->mlx->wptr, keycode, data);
  mlx_mouse_hook(data->mlx->wptr, mousecode, data);
  mlx_loop(data->mlx->mptr);
  return (0);
}
