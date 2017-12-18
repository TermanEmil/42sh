#ifndef EVENTLIB_H
# define EVENTLIB_H

# include "listlib.h"
# include "hashtablib.h"

typedef struct s_event_instance	t_event_instance;

typedef void (t_handler_f)(void*);

struct				s_event_instance
{
	t_handler_f		*f;
	void			*f_data;
};

/*
** Defined in events_init_globals.c
** It's a general storage of events, used, in first place, by event_exit()
*/

extern t_hashtab	*g_events;

/*
** event construct / destruct
*/

t_event_instance	event_instance_construct(t_handler_f *handler, void *data);
t_event_instance	event_inst_new(t_handler_f *handler, void *data);
void				event_instance_destruct(t_event_instance *instance);
t_hashtab			*events_construct(size_t len);
void				events_destruct(t_hashtab **events);

/*
** Events add
*/

void				event_add(t_hashtab *events, char *key,
						t_event_instance event);
void				event_quick_add(t_hashtab *events, char *key,
						t_handler_f *handler, void *data);

/*
** Events run
*/

void				event_run(t_event_instance const *event);
void				events_run_first(t_hashtab *events, char const *key);
void				events_run_all(t_hashtab *events, char const *key);
void				events_run_iter_matching(t_hashtab *events,
						char const *key, t_cmp_f *cmp_f);

/*
** Events remove
*/

void				events_remove_with_key(t_hashtab *events, char const *key);
void				events_rm_iter_matching(t_hashtab *events,
						char const *key, t_cmp_f *cmp_f);

/*
** Global stuff
*/

void				events_init_globals(size_t starting_nr_of_events);
void				event_global_force_add(char *key, t_event_instance event);

/*
** event_exit:
** it listens to all 'event_exit*' and 'memory_frees*' events
*/

void				event_exit(int status);

#endif