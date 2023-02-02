#include "render.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>

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

int	init_renderer(t_renderer	*renderer)
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
	if (!renderer->img.depths)
		return (1);
	renderer->img.depths[0].pixel_x = -1;
	return (0);
}

int	destroy_renderer(t_renderer	*renderer)
{
	int	return_value;

	return_value = mlx_destroy_window(renderer->mlx, renderer->window);
	return_value += mlx_destroy_image(renderer->mlx, renderer->img.addr);
	//return_value += mlx_loop_end(renderer->mlx);
	return_value += mlx_destroy_display(renderer->mlx);
	free(renderer->mlx);
	free(renderer->img.depths);
	return (return_value);
}
