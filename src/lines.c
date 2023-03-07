#include "render.h"
#include <stddef.h>
#include <math.h>

static int	abs(int x)
{
	return ((x) * ((x > 0) * 2 -1));
}

static void	get_color_step(
	double *res, t_pixel start, t_pixel end, double step_nb)
{
	res[0] = (((end.color >> 16) & 0xFF) -((start.color >> 16) & 0xFF))
		/ step_nb;
	res[1] = (((end.color >> 8) & 0xFF) -((start.color >> 8) & 0xFF)) / step_nb;
	res[2] = ((end.color & 0xFF) -(start.color & 0xFF)) / step_nb;
}

void	draw_horizontal_line(t_renderer *renderer, t_pixel start, t_pixel end)
{
	const int		step_nb = abs(start.x - end.x);
	const double	depth_step = (end.depth - start.depth) / step_nb;
	const double	y_step = (double)(end.y - start.y) / step_nb;
	double			color_step[3];
	int				i;

	get_color_step(color_step, start, end, step_nb);
	i = 0;
	while (i < step_nb)
	{
		put_pixel(&renderer->images, (t_pixel){
			start.depth + depth_step * i,
			start.x + ((end.x - start.x > 0) * 2 -1) * i,
			start.y + y_step * i,
			start.color + (((int)(color_step[0] * i)) << 16)
			+ (((int)(color_step[1] * i) << 8)) + (int)(color_step[2] * i)
		});
		i++;
	}
}

void	draw_vertical_line(t_renderer *renderer, t_pixel start, t_pixel end)
{
	const int		step_nb = abs(start.y - end.y);
	const double	depth_step = (end.depth - start.depth) / step_nb;
	const double	x_step = (double)(end.x - start.x) / step_nb;
	double			color_step[3];
	int				i;

	get_color_step(color_step, start, end, step_nb);
	i = 0;
	while (i < step_nb)
	{
		put_pixel(&renderer->images, (t_pixel){
			start.depth + depth_step * i,
			start.x + x_step * i,
			start.y + ((end.y - start.y > 0) * 2 -1) * i,
			start.color + (((int)(color_step[0] * i)) << 16)
			+ (((int)(color_step[1] * i)) << 8) + (int)(color_step[2] * i)
		});
		i++;
	}
}

void	draw_line(t_renderer *renderer, t_point p1, t_point p2)
{
	const t_pixel	pix_1 = project(renderer, p1);
	const t_pixel	pix_2 = project(renderer, p2);

	if ((pix_1.x < 0 && pix_2.x < 0)
		|| (pix_1.x >= renderer->images.w && pix_2.x >= renderer->images.w)
		|| (pix_1.y < 0 && pix_2.y < 0)
		|| (pix_1.y >= renderer->images.h && pix_2.y >= renderer->images.h))
		return ;
	// @TODO add a check to know how to start if points are out of the screen
	// tips : use ax + b == 0 to get the intersection between line and origin
	if (abs(pix_2.y - pix_1.y) > abs(pix_2.x - pix_1.x))
		draw_vertical_line(renderer, pix_1, pix_2);
	else
		draw_horizontal_line(renderer, pix_1, pix_2);
}
