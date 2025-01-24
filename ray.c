#include "Includes/minirt.h"

t_ray	ray(t_point p, t_vector v)
{
	t_ray	r;

	r.origin = p;
	r.direction = v;
	return (r);
}

t_point	position(t_ray r, double t)
{
	return (add_tuple(r.origin, mult_tuple(r.direction, t)));
}

//| Próximo passo de acordo com o livro é implementar a função de interseção.
//| Mas pelo que eu entendi a função de interseção tem que entrar intersection(t_object o, t_ray r),
//| sendo t_object qualquer um dos objetos, mas o objeto que ele mostra como exemplo é a esfera.
