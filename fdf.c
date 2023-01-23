#include "fdf.h"
#include "render.h"
#include <mlx.h>
#include <X11/X.h>
#include <stddef.h>
#include <stdio.h> // @TODO rm if final

int	key_hook(int keycode, void *param)
{
	printf("TEST -> %d, %p", keycode, param);
	return (0);
}

int	tick(t_renderer *renderer)
{
	(void) renderer;
	//printf("Tick\n");
	return (0);
}

int	main(void)
{
	t_renderer	renderer;

	init_renderer(&renderer);

	put_origins(&renderer);
	put_cube(&renderer, (t_point){-50, -50, 0, -1}, 100);

	mlx_put_image_to_window(renderer.mlx, renderer.window, renderer.img.addr, 0, 0);
	mlx_key_hook(renderer.window, key_hook, NULL); // @TODO
	mlx_loop_hook(renderer.mlx, tick, &renderer);
	mlx_loop(renderer.mlx);
	mlx_destroy_window(renderer.mlx, renderer.window);
	mlx_destroy_display(renderer.mlx);
}
