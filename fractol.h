
#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIDTH 800
# define HEIGHT 800

typedef struct  mlx
{
  void   *mptr;
  void   *wptr;
	void   *img_ptr;
	int    *data;
	int    size_l;
	int    bpp;
	int    endian;
}							  t_mlx;

typedef struct  fract
{
  double z;
  float startx;
  float endx;
  float starty;
  float endy;
  int   zoom;
  int   itmax;
  float imgx;
  float imgy;
  double   c_r;
  double   c_i;
  double   z_r;
  double   z_i;
  t_mlx *mlx;
}               t_fract;

int   keycode(int key, t_fract *data);
int   mousecode(int button, int x, int y, t_fract *data);
void  mandelbrot(t_fract *data, int x, int y);
#endif
