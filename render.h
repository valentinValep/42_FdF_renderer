#ifndef RENDER_H
# define RENDER_H

# define WINDOW_W 1920
# define WINDOW_H 1080
# define PROJECTIONS_NUMBER 2
# define _XOPEN_SOURCE 500 // Use for math.h in render.c

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_depth
{
	double	value;
	int		pixel_x;
	int		pixel_y;
}	t_depth;

typedef struct s_img
{
	void	*addr;
	char	*pixels;
	t_depth	*depths;
	int		h;
	int		w;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_projection_matrix
{
	char	*name;
	double	i_hat[2];
	double	j_hat[2];
	double	k_hat[2];
}	t_projection_matrix;

typedef struct s_renderer
{
	t_img				img;
	void				*mlx;
	void				*window;
	t_projection_matrix	projections[PROJECTIONS_NUMBER];
	int					projection_select;
	int					origin_x;
	int					origin_y;
}	t_renderer;

void	init_renderer(t_renderer	*renderer);
int		put_point(t_renderer	*renderer, t_point *point);
void	put_origins(t_renderer	*renderer);
void	put_cube(t_renderer	*renderer, t_point start, double w);
void	put_line(t_renderer	*renderer, t_point p1, t_point p2);

#endif