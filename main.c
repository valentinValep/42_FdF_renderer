#include <unistd.h>
#include <stdlib.h>
#include "render.h"
#include "mlx.h"

int	hook_destroy(t_renderer *renderer)
{
	return (mlx_loop_end(renderer->mlx));
}

int	main(void)
{
	t_renderer	renderer;

	if (init_renderer(&renderer))
	{
		write(STDERR_FILENO, "Renderer initialisation failed\n", 31);
		exit(1);
	}

	put_origins(&renderer);
	draw_cube(&renderer, (t_point){20., -20., -20., 0x00FFFF00}, 50.);
	render_tick(&renderer);

	mlx_hook(renderer.window, 17, 0, hook_destroy, &renderer);
	mlx_loop(renderer.mlx);
	if (destroy_renderer(&renderer))
	{
		write(STDERR_FILENO, "Renderer destruction failed\n", 28);
		exit(1);
	}
}
