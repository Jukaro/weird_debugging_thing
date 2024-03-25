#include "launcher.h"

static t_dbg_info	*dbg_new(char *title, char *name, char **names, char *color)
{
	t_dbg_info	*new = malloc(sizeof(t_dbg_info));

	int	nb_info = 0;

	while (names[nb_info])
		nb_info++;
	new->info_array = malloc(sizeof(t_info) * (nb_info + 1));
	for (int i = 0; names[i]; i++)
	{
		new->info_array[i].info = NULL;
		new->info_array[i].name = names[i];
	}
	new->info_array[nb_info].info = NULL;
	new->info_array[nb_info].name = NULL;

	new->name = name;
	new->category_title = title;
	new->color = color;
	new->counter = 0;
	new->next = NULL;
	return (new);
}

static void	dbg_addback(t_dbg_info **list, t_dbg_info *elem)
{
	t_dbg_info	*last_elem;

	if (*list == NULL)
	{
		*list = elem;
		return;
	}
	last_elem = *list;
	while (last_elem->next != NULL)
		last_elem = last_elem->next;
	last_elem->next = elem;
}

int		dbg_list_size(t_dbg_info *list)
{
	int	size = 0;
	t_dbg_info	*ptr = list;

	while (ptr)
	{
		ptr = ptr->next;
		size++;
	}
	return (size);
}

void	dbg_free_list(t_dbg_info **list)
{
	t_dbg_info	*ptr;
	t_dbg_info	*before_elem;

	ptr = *list;
	if (ptr == NULL || list == NULL)
		return ;
	while (ptr != NULL)
	{
		free_d_info(ptr);
		before_elem = ptr;
		ptr = ptr->next;
		free(before_elem);
	}
	*list = NULL;
}

void	init_dbg_lists(t_dbg_info **r_list, t_dbg_info **e_list)
{
	char	*paquet_nb[] = {
		"NB PAQUETS RECU",
		"NUM PAQUET ATTENDU",
		NULL
	};

	char	*e_infos[] = {
		"NB PAQUETS ENVOYE",
		"NB PAQUETS RECU",
		"BORNE_INF",
		NULL
	};

	char	*paquet_info1[] = {
		"NUM_SEQ",
		"SOMME_CONTROLE",
		"SOMME_CONTROLE_RECEPTION",
		NULL
	};

	char	*paquet_info2[] = {
		"NUM_SEQ",
		"SOMME_CONTROLE",
		"SOMME_CONTROLE_RECEPTION",
		"TRAITEMENT",
		NULL
	};

	dbg_addback(r_list, dbg_new("INFOS", "R_NB_PAQUETS", paquet_nb, PURPLE));
	dbg_addback(r_list, dbg_new("DERNIER PAQUET RECU", "R_DERNIER_PAQUET_RECU", paquet_info2, YELLOW));
	dbg_addback(r_list, dbg_new("PAQUET PLUS PROCHE", "R_PAQUET_PLUS_PROCHE", paquet_info2, YELLOW));
	dbg_addback(r_list, dbg_new("DERNIER ACK ENVOYE", "R_DERNIER_ACK_ENVOYE", paquet_info1, YELLOW));
	dbg_addback(e_list, dbg_new("INFOS", "E_INFOS", e_infos, PURPLE));
	dbg_addback(e_list, dbg_new("DERNIER ACK RECU", "E_DERNIER_ACK_RECU", paquet_info1, YELLOW));
	dbg_addback(e_list, dbg_new("DERNIER ACK VALIDE", "E_DERNIER_ACK_VALIDE", paquet_info1, GREEN));
}

void	free_d_info(t_dbg_info *info)
{
	for (int i = 0; info->info_array[i].name; i++)
		free(info->info_array[i].info);
	free(info->info_array);
}

int	print_info(t_dbg_info *info, int row, int col)
{
	info->counter++;
	if (col == 1)
	{
		gotoxy(row, SEP);
		printf("\e[?1K");
	}
	else
	{
		gotoxy(row, col);
		printf("%s", CLR);
	}
	gotoxy(row, col);
	printf("fd %d (%d)", info->pipe[0], info->counter);
	for (int i = 0; info->info_array[i].name; i++)
	{
		free(info->info_array[i].info);
		info->info_array[i].info = get_next_line(info->pipe[0]);
		if (!info->info_array[i].info || !info->info_array[i].info[0])
			return (1);
		if (col == 1)
		{
			gotoxy(info->info_array[i].row, SEP);
			printf("\e[?1K");
		}
		else
		{
			gotoxy(info->info_array[i].row, info->info_array[i].col);
			printf("%s", CLR);
		}
		gotoxy(info->info_array[i].row, info->info_array[i].col);
		printf("%s", info->info_array[i].info);

	}
	return (0);
}
