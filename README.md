# Renderer for 42_FdF
This is a library used to render a 3D wireframe for a 42 school project : [FdF](https://github.com/valentinValep/42_Fdf).

# Usage

## Compilation

To use this lib you need to compile with the [minilibx](https://github.com/42Paris/minilibx-linux).

## Exemple

```c
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
	draw_line(&renderer, (t_point){-100, 100, 300, 0x00FFFF00}, (t_point){100, 0, 300, 0x0000FF00});
	render_tick(&renderer);

	mlx_hook(renderer.window, 17, 0, hook_destroy, &renderer);
	mlx_loop(renderer.mlx);
	if (destroy_renderer(&renderer))
	{
		write(STDERR_FILENO, "Renderer destruction failed\n", 28);
		exit(1);
	}
}
```

# ROADMAP (stand by)
-	Custom projection matrix
-	Custom window size
-	Change line draw algorithm
-	Command helper on another img

# Credits
This project was developed by [valentinValep](https://github.com/valentinValep). The project was completed using the C programming language and the minilibx library.
