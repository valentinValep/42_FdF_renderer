#include "render.h"
#include <mlx.h>

int	put_pixel(t_renderer	*renderer, int x, int y, int color)
{
	if (x < 0 || x > renderer->img.w)
		return (0);
	if (y < 0 || y > renderer->img.h)
		return (0);
	((int *)renderer->img.pixels)[x % renderer->img.w + y * renderer->img.w]
		= color;
	return (1);
}

int	is_fronter_pixel(t_renderer	*renderer, int x, int y, int depth)
{
	int	i;

	i = 0;
	while (renderer->img.depths[i].pixel_x != -1
		&& (renderer->img.depths[i].pixel_x != x
			|| renderer->img.depths[i].pixel_y != y))
		i++;
	if (renderer->img.depths[i].pixel_x != -1)
	{
		if (depth <= renderer->img.depths[i].value)
			return (0);
		renderer->img.depths[i].pixel_x = x;
		renderer->img.depths[i].pixel_y = y;
		renderer->img.depths[i].value = depth;
	}
	else
	{
		renderer->img.depths[i].pixel_x = x;
		renderer->img.depths[i].pixel_y = y;
		renderer->img.depths[i].value = depth;
		renderer->img.depths[i + 1].pixel_x = -1;
	}
	return (1);
}

// @TODO Care to reset it before re-use it for another img
int	draw_point(t_renderer	*renderer, t_point *point)
{
	int const	pixel_x
		= point->x * renderer->projections[renderer->projection_select].i_hat[0]
		+ point->y * renderer->projections[renderer->projection_select].j_hat[0]
		+ point->z * renderer->projections[renderer->projection_select].k_hat[0]
		+ renderer->origin_x;
	int const	pixel_y
		= point->x * renderer->projections[renderer->projection_select].i_hat[1]
		+ point->y * renderer->projections[renderer->projection_select].j_hat[1]
		+ point->z * renderer->projections[renderer->projection_select].k_hat[1]
		+ renderer->origin_y;

	if (pixel_x < 0 || pixel_x > renderer->img.w
		|| pixel_y < 0 || pixel_y > renderer->img.h)
		return (0);
	if (is_fronter_pixel(
			renderer, pixel_x, pixel_y, point->x + point->y + point->z))
		return (put_pixel(renderer, pixel_x, pixel_y, point->color));
	return (1);
}
