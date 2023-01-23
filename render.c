#include "render.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

int	put_pixel(t_renderer	*renderer, int x, int y, int color)
{
	x += renderer->origin_x;
	y += renderer->origin_y;
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
		if (depth > renderer->img.depths[i].value)
		{
			renderer->img.depths[i].pixel_x = x;
			renderer->img.depths[i].pixel_y = y;
			renderer->img.depths[i].value = depth;
			return (1);
		}
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
int	put_point(t_renderer	*renderer, t_point *point)
{
	int const	pixel_x
		= point->x * renderer->projections[renderer->projection_select].i_hat[0]
		+ point->y * renderer->projections[renderer->projection_select].j_hat[0]
		+ point->z * renderer->projections[renderer->projection_select].k_hat[0]
		;
	int const	pixel_y
		= point->x * renderer->projections[renderer->projection_select].i_hat[1]
		+ point->y * renderer->projections[renderer->projection_select].j_hat[1]
		+ point->z * renderer->projections[renderer->projection_select].k_hat[1]
		;

	if (pixel_x < 0 || pixel_x > renderer->img.w || pixel_y < 0 || pixel_y > renderer->img.h)
		return (0);
	if (is_fronter_pixel(renderer, pixel_x, pixel_y, point->x + point->y + point->z))
		return (put_pixel(renderer, pixel_x, pixel_y, point->color));
	return (0);
}

void	init_projections(t_renderer	*renderer)
{
	renderer->projections[0].name = "Isometric"; // @TODO verif this string is not delete
	renderer->projections[0].i_hat[0] = cos(M_PI / 6.);
	renderer->projections[0].i_hat[1] = sin(M_PI / 6);
	renderer->projections[0].j_hat[0] = cos(5. * M_PI / 6.);
	renderer->projections[0].j_hat[1] = sin(5. * M_PI / 6.);
	renderer->projections[0].k_hat[0] = 0.;
	renderer->projections[0].k_hat[1] = -1.;
	renderer->projections[1].name = "Military"; // @TODO verif this string is not delete
	renderer->projections[1].i_hat[0] = 1;
	renderer->projections[1].i_hat[1] = 1;
	renderer->projections[1].j_hat[0] = -1;
	renderer->projections[1].j_hat[1] = 1;
	renderer->projections[1].k_hat[0] = 0.;
	renderer->projections[1].k_hat[1] = -1.;
}

void	init_renderer(t_renderer	*renderer)
{
	renderer->mlx = mlx_init();
	renderer->window = mlx_new_window(renderer->mlx, WINDOW_W, WINDOW_H, "Test isometrique");
	renderer->origin_x = WINDOW_W / 2;
	renderer->origin_y = WINDOW_H / 2;
	renderer->img.addr = mlx_new_image(renderer->mlx, WINDOW_W, WINDOW_H);
	renderer->img.w = WINDOW_W;
	renderer->img.h = WINDOW_H;
	renderer->img.pixels = mlx_get_data_addr(renderer->img.addr, &renderer->img.bits_per_pixel, &renderer->img.line_len, &renderer->img.endian);
	renderer->origin_x = WINDOW_W / 2;
	renderer->origin_y = WINDOW_H / 2;
	init_projections(renderer);
	renderer->projection_select = 0;
	renderer->img.depths = malloc(WINDOW_W * WINDOW_H * sizeof(t_depth)); // @TODO Implement it as a variable lenght struct
	renderer->img.depths[0].pixel_x = -1;
}
