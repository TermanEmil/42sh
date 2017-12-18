#ifndef HASHTABLIB_H
# define HASHTABLIB_H

# include "libft.h"
# include <stdio.h>

# define HTAB_SEARCHING_FOR_FREE_CELL 1

/*
** It's open addressing hash table
*/

typedef struct s_hashtab	t_hashtab;
typedef struct s_hashpair	t_hashpair;
typedef struct s_hashmem	t_hashmem;

/*
** This dummy value is placed instead of the removed bucket.
** in new_hashpair.c
** https://youtu.be/EJOIt0KWFr4?t=2m23s
*/

extern t_hashpair const		g_htab_dummy;

/*
** Function typedefs
*/

typedef void	(t_del_mem_f)(void*, size_t);
typedef size_t	(t_hash_f)(void const*, size_t);
typedef int		(t_cmp_f)(void const *a, void const *b, size_t a_s, size_t b_s);
typedef void	(t_const_iter_f)(t_hashpair const*);

/*
** hash collision function (function which resolves collision)
*/

typedef ssize_t	(t_hashcol_f)(t_hashtab const*, void const*,
					size_t, int search_free_cell);

struct			s_hashmem
{
	void		*mem;
	size_t		size;
};

struct			s_hashpair
{
	t_hashmem	key;
	t_hashmem	val;
};

/*
** kdel, vdel: functions used to delete the memory of key and value.
** hash_f: function which is used to hash the key, it's set by default to be
**     ft_hash()
** hashcol_f: function which deals with collisions, set to linear probing
**     by default.
*/

struct			s_hashtab
{
	t_hashpair	**tab;
	size_t		tablen;
	size_t		free_cells;
	t_del_mem_f	*kdel;
	t_del_mem_f	*vdel;
	t_cmp_f		*cmp_f;
	t_hash_f	*hash_f;
	t_hashcol_f	*hashcol_f;
};

/*
** Hashmem
** The `*_cp' functions, allocate a new memory for the mem.
*/

t_hashmem		new_hashmem(void *mem, size_t size);
t_hashmem		new_hashmem_cp(void const *mem, size_t size);

/*
** String hashmem.
*/

t_hashmem		new_hashmem_str(char *str);
t_hashmem		new_hashmem_str_cp(char const *str);

/*
** Hashpair
** `new_haspair' returns a pointer of a static value.
*/

t_hashpair		*new_hashpair(t_hashmem key, t_hashmem val);
t_hashpair		*new_hashpair_mllc(t_hashmem key, t_hashmem val);									
void			del_hashpair(t_hashpair **pair,
					t_del_mem_f *kdel, t_del_mem_f *vdel);

/*
** Hashtab
*/

t_hashtab		*new_hashtab(size_t tablen,
					t_del_mem_f *kdel, t_del_mem_f *vdel);
void			del_hashtab(t_hashtab **tab);
ssize_t			get_key_index(t_hashtab const *htab, t_hashmem key,
					int search_free_cell);
t_hashpair		*get_hashpair(t_hashtab const *htab, t_hashmem key);
int				hashtab_add_pair(t_hashtab *htab, t_hashpair *newpair);
void			htab_iter(t_hashtab *htab, t_const_iter_f *f);
void			htab_rehash(t_hashtab *htab, size_t size_to_add);
float			hashtab_load_factor(t_hashtab const *hashtab);
ssize_t			htab_remove_at(t_hashtab *hashtab, ssize_t index);
ssize_t			htab_remove(t_hashtab *hashtab, t_hashmem key);
t_hashpair		*htab_get_next_pair(t_hashtab *htab, t_hashmem key,
					ssize_t *last_i, ssize_t *start);
t_hashpair		*htab_get_next_pair_iter(t_hashtab *htab, t_hashmem key,
					ssize_t *last_i, t_cmp_f *cmp_f);
ssize_t			htab_index_of(t_hashtab const *htab, t_hashpair const *pair);

/*
** Hash functions
*/

size_t			ft_hash(void const *key, size_t len);
size_t			get_hindex(t_hashtab const *htab,
					void const *key, size_t ksize);

/*
** Resolving collision functions (linear probing, plus n refresh,
** quadratic probing, double hashing)
*/

ssize_t			hash_linear_probing_method(t_hashtab const *htab,
					void const *key, size_t ksize, int search_free_cell);

/*
** Standard Hashtab functions
*/

void			std_str_print_hashpair(t_hashpair const *pair);
void			std_mem_print_hashpair(t_hashpair const *pair);
int				std_htab_mem_cmp(void const *a, void const *b,
					size_t asize, size_t bsize);
int				std_htab_str_match(char const *a, char const *b);

#endif