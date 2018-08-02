
int int_to_color(unsigned int color)
{
	int r;
	int g;
	int b;
	int res;

	r = (color >> 16) & 0x0FF;
	g = (color >> 8) & 0x0FF;
	b = color & 0x0FF;
	res = (r << 16) + (g << 8) + b;
	return (res);
}

int   hsvtorgb(double hue, double s, double v)
{
  int i;
  double f;
  double p;
  double q;
  double t;

  if(s == 0)
    return (int_to_color(((int)v << 16) + ((int)v << 8) + v));
  hue /= 60 % 6;
  i = hue;
  f = hue - i;
  p = v * (1 - s));
  q = v * (1 - s * f));
  t = v * (1- s * (1 - f)));
  if (i == 0)
    return (int_to_color(((int)v << 16) + (t << 8) + p));
  if (i == 1)
    return (int_to_color((q << 16) + ((int)v << 8) + p));
  if (i == 2)
    return (int_to_color((p << 16) + ((int)v << 8) + t));
  if (i == 3)
    return (int_to_color((p << 16) + (q << 8) + (int)v));
  if (i == 4)
    return (int_to_color((t << 16) + (p << 8) + (int)v));
  return (int_to_color(((int)v << 16) + (p << 8) + q));
}

int  smoothcolor(double i, double z_r, double z_i)
{
  double di;
  double zn;
  double hue;

  di = i;
  zn = sqrt(z_r + z_i);
  hue = di + 1.0 - log(log(fabs(zn))) / log(2.0);
  // hue = 0.95 + 20.0 * hue;
  while (hue > 360.0)
    hue -= 1.0;
  while (hue < 0)
    hue += 1.0;
  return (hsvtorgb(hue, 0.8, 1.0));
}
