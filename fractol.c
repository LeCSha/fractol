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
  data->zoom = 0.5;
  data->startx = 0;
  data->endx = 0;
  data->starty = 0;
  data->endy = 0;
  data->imgx = WIDTH;
  data->imgy = HEIGHT;
}

void init_julia(t_fract *data)
{
  data->itmax = 50;
  data->zoom = 0.5;
  data->startx = 0;
  data->endx = 0;
  data->starty = 0;
  data->endy = 0;
  data->imgx = WIDTH;
  data->imgy = HEIGHT;
  // data->c_r = 0.285; //nonfilled
  // data->c_i = 0.01; //nonfilled
  // data->c_r = 1.4; //max
  // data->c_i = 1.9; //max
  // data->c_r = -0.32; //filled
  // data->c_i = 0.90; //filled
  data->c_r = 0;
  data->c_i = 0;
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
      // data->c_r = (x * (data->endx - data->startx)) / data->zoom + data->starty;
      // data->c_i = (y * (data->starty - data->endy)) / data->zoom + data->endy;
      data->c_r = 1.0 * (x - WIDTH / 2) / (0.5 * data->zoom * WIDTH) + data->startx;
      data->c_i = (y - HEIGHT / 2) / (0.5 * data->zoom * HEIGHT) + data->starty;
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
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, 0x000000);
        draw_fractal(data, x, y, 0x000000);
      else
      {
        // i = i - log(log(sqrt(data->z_r * data->z_r + data->z_i * data->z_r))) / log(2);
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, i * (0xFF0000 / data->itmax) / 50);
        // i = i + 1 - log(log(fabs(data->z_r * data->z_r + data->z_i * data->z_r))) / log(2);
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, (int)(i * 0x84742d / data->itmax) >> 16);
        i = i - log(log(fabs(data->z_r * data->z_r + data->z_i * data->z_i))) + 4;
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, i * 0x84742d / data->itmax);
        draw_fractal(data, x, y, i * i);
        // draw_fractal(data, x, y, i * (0x84742d / data->itmax) / 50);
      }
      x++;
    }
    x = 0;
    y++;
  }
}
int   set_color(double i)
{
    int clr;

    clr = 0;
    i = sin(i) * 100;
    if (i < 0)
      clr = 0x8f8ad;
    else if (i >= 0 && i < 20)
      clr = 0x6b4e90;
    else if (i >= 20 && i < 35)
      clr = 0x744b90;
    else if (i >= 35 && i < 50)
      clr = 0x3a1354;
    else if (i >= 50 && i < 60)
      clr = 0x4c2d73;
    else if (i >= 60 && i < 70)
      clr = 0x552b72;
    else if (i >= 70 && i < 80)
      clr = 0x321456;
    else
      clr = 0x1c053a;
    return (clr);
}

void julia(t_fract *data, int x, int y)
{
  double i;
  double tmp;

  while (y < data->imgy)
  {
    while (x < data->imgx)
    {
      data->z_r = 1.0 * (x - WIDTH / 2) / (0.5 * data->zoom * WIDTH) + data->startx;
      data->z_i = (y - HEIGHT / 2) / (0.5 * data->zoom * HEIGHT) + data->starty;
      i = 0;
      while ((data->z_r * data->z_r + data->z_i * data->z_i)< 4 && i < data->itmax)
      {
        tmp = data->z_r;
        data->z_r = data->z_r * data->z_r - data->z_i * data->z_i - 0.8 + data->c_r;
        data->z_i = 2 * tmp * data->z_i + data->c_i;
        i++;
      }
      if (i == data->itmax)
        draw_fractal(data, x, y, 0x000000);
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, 0x000000);
      else
      {
        i = i - log(log(fabs(data->z_r * data->z_r + data->z_i * data->z_i))) + 4;
        // mlx_pixel_put(data->mlx->mptr, data->mlx->wptr, x, y, i * i * 0.1 * data->itmax);
        // draw_fractal(data, x, y, i * i * 0.1 * data->itmax);
        draw_fractal(data, x, y, i * i );
      }
      x++;
    }
    x = 0;
    y++;
  }
}

int main(int ac, char **av)
{
  t_fract *data;

  if (!(data = (t_fract *)malloc(sizeof(t_fract))))
    print_error(1, data);
  init_mlx(data);
  if (ac < 1)
    return (0);
  if (ft_strcmp("mandelbrot" ,av[1]) == 0)
  {
    init_mandel(data);
    mandelbrot(data, 0, 0);
  }
  if (ft_strcmp("julia", av[1]) == 0)
  {
    init_julia(data);
    julia(data, 0, 0);
  }
  mlx_put_image_to_window(data->mlx->mptr, data->mlx->wptr, data->mlx->img_ptr, 0, 0);
  mlx_key_hook(data->mlx->wptr, keycode, data);
  // mlx_mouse_hook(data->mlx->wptr, mousecode, data);
  mlx_loop(data->mlx->mptr);
  return (0);
}
