#include "render.h"
#include <mlx.h>

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

int	put_point(t_renderer	*renderer, t_point *point)
{
	int const	pixel_x = point->x * PROJECTION_MATRIX_I_HAT[0]
		+ point->y * PROJECTION_MATRIX_J_HAT[0]
		+ point->z * PROJECTION_MATRIX_K_HAT[0];
	int const	pixel_y = point->x * PROJECTION_MATRIX_I_HAT[1]
		+ point->y * PROJECTION_MATRIX_J_HAT[1]
		+ point->z * PROJECTION_MATRIX_K_HAT[1];

	return (put_pixel(renderer, pixel_x, pixel_y, point->color));
}

void	init_renderer(t_renderer	*renderer)
{
	renderer->mlx = mlx_init();
	renderer->window = mlx_new_window(renderer->mlx, 1920, 1080, "Test isometrique");
	renderer->origin_x = 1920 / 2;
	renderer->origin_y = 1080 / 2;
	renderer->img.addr = mlx_new_image(renderer->mlx, 1920, 1080);
	renderer->img.w = 1920;
	renderer->img.h = 1080;
	renderer->img.pixels = mlx_get_data_addr(renderer->img.addr, &renderer->img.bits_per_pixel, &renderer->img.line_len, &renderer->img.endian);
	renderer->origin_x = 1920 / 2;
	renderer->origin_y = 1080 / 2;
}
