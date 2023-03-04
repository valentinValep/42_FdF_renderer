#include "render.h"
#include <stddef.h>
#include <math.h>

static int	abs(int x)
{
	return ((x) * ((x > 0) * 2 -1));
}

void	draw_horizontal_line(t_renderer *renderer, t_pixel start, t_pixel end)
{
	const int		step_nb = abs(start.x - end.x);
	const double	depth_step = (end.depth - start.depth / step_nb);
	const double	y_step = (end.y - start.y / step_nb);
	//const double	color_step = ; @TODO
	int				i;

	i = 0;
	while (i < step_nb)
	{
		put_pixel(&renderer->images, (t_pixel){
			start.depth + depth_step * i,
			start.x + i,
			start.y + y_step * i,
			start.color});
		i++;
	}
}

void	draw_vertical_line(t_renderer *renderer, t_pixel start, t_pixel end)
{
	const int		step_nb = abs(start.y - end.y);
	const double	depth_step = (end.depth - start.depth / step_nb);
	const double	x_step = (end.x - start.x / step_nb);
	//const double	color_step = ; @TODO
	int				i;

	i = 0;
	while (i < step_nb)
	{
		put_pixel(&renderer->images, (t_pixel){
			start.depth + depth_step * i,
			start.x + x_step * i,
			start.y + i,
			start.color});
		i++;
	}
}

void	draw_line(t_renderer *renderer, t_point p1, t_point p2)
{
	const t_pixel	pix_1 = project(renderer, p1);
	const t_pixel	pix_2 = project(renderer, p2);

	if (abs(pix_2.y - pix_1.y) > abs(pix_2.x - pix_1.x))
		draw_vertical_line(renderer, pix_1, pix_2);
	else
		draw_horizontal_line(renderer, pix_1, pix_2);
}
