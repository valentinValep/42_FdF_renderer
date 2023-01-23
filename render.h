#ifndef RENDER_H
# define RENDER_H

# define _XOPEN_SOURCE 500
# include <math.h>

// @TODO put these in projection in renderer
# define PROJECTION_MATRIX_I_HAT (double []){cos(M_PI / 6.), sin(M_PI / 6)}
# define PROJECTION_MATRIX_J_HAT (double []){cos(5. * M_PI / 6.), sin(5. * M_PI / 6.)}
# define PROJECTION_MATRIX_K_HAT (double []){0., -1.}

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_img
{
	void	*addr;
	char	*pixels;
	int		*depths; // @TODO
	int		h;
	int		w;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_renderer
{
	t_img	img;
	void	*mlx;
	void	*window;
	double	*projection; // @TODO
	int		origin_x;
	int		origin_y;
}	t_renderer;

void	init_renderer(t_renderer	*renderer);
int	put_point(t_renderer	*renderer, t_point *point);
void	put_origins(t_renderer	*renderer);
void	put_cube(t_renderer	*renderer, t_point start, double w);
void	put_line(t_renderer	*renderer, t_point p1, t_point p2);

#endif