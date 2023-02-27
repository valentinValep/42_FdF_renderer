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
	//draw_line(&renderer, (t_point){-40, 700000, 0, -1}, (t_point){60, -10000000, 0, -1});
	//draw_line(&renderer, (t_point){-50, 700000, 0, -1}, (t_point){70, -10000000, 0, -1});
	//draw_line(&renderer, (t_point){-60, 700000, 0, -1}, (t_point){80, -10000000, 0, -1});
	//draw_line(&renderer, (t_point){-140, 700000, 0, -1}, (t_point){60, -10000000, 0, -1});
	//draw_line(&renderer, (t_point){-150, 700000, 0, -1}, (t_point){70, -10000000, 0, -1});
	//draw_line(&renderer, (t_point){-160, 700000, 0, -1}, (t_point){80, -10000000, 0, -1});
	//draw_line(&renderer, (t_point){-400, 700, 0, -1}, (t_point){600, -700, 0, -1});
	//draw_line(&renderer, (t_point){-500, 700, 0, -1}, (t_point){500, -700, 0, -1});
	//draw_line(&renderer, (t_point){-600, 700, 0, -1}, (t_point){400, -700, 0, -1});
	//draw_line(&renderer, (t_point){-700, 700, 0, -1}, (t_point){300, -700, 0, -1});
	//draw_line(&renderer, (t_point){-800, 700, 0, -1}, (t_point){200, -700, 0, -1});
	//draw_line(&renderer, (t_point){-450, 700, 0, -1}, (t_point){600, -700, 0, -1});
	//draw_line(&renderer, (t_point){-550, 700, 0, -1}, (t_point){500, -700, 0, -1});
	//draw_line(&renderer, (t_point){-650, 700, 0, -1}, (t_point){400, -700, 0, -1});
	//draw_line(&renderer, (t_point){-750, 700, 0, -1}, (t_point){300, -700, 0, -1});
	//draw_line(&renderer, (t_point){-850, 700, 0, -1}, (t_point){200, -700, 0, -1});
	//draw_line(&renderer, (t_point){-470, 700, 0, -1}, (t_point){600, -700, 0, -1});
	//draw_line(&renderer, (t_point){-570, 700, 0, -1}, (t_point){500, -700, 0, -1});
	//draw_line(&renderer, (t_point){-670, 700, 0, -1}, (t_point){400, -700, 0, -1});
	//draw_line(&renderer, (t_point){-770, 700, 0, -1}, (t_point){300, -700, 0, -1});
	//draw_line(&renderer, (t_point){-870, 700, 0, -1}, (t_point){200, -700, 0, -1});

	//draw_cube(&renderer, (t_point){20., -20., -20., 0x00FFFF00}, 50.);
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){200, -200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){200, 0, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){200, -50, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){200, 50, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){200, 200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){0, 200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){50, 200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-50, 200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, 200, 0, -1});

	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, 200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, 0, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, 50, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, -50, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, -200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){0, -200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){50, -200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-50, -200, 0, -1});
	//draw_line(&renderer, (t_point){0, 0, 0, -1}, (t_point){-200, -200, 0, -1});
	render_tick(&renderer);

	mlx_hook(renderer.window, 17, 0, hook_destroy, &renderer);
	mlx_loop(renderer.mlx);
	if (destroy_renderer(&renderer))
	{
		write(STDERR_FILENO, "Renderer destruction failed\n", 28);
		exit(1);
	}
}
