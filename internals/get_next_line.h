#ifndef __GET_NEXT_LINE_H__
# define __GET_NEXT_LINE_H__


# define BUFF_SIZE 2
# define FULL_LINE 1
# define TRUNCATED_LINE 0

typedef short LineManagement;

char*	get_next_line(const int fd);
void	set_get_next_line_full_or_truncated(LineManagement v);

#endif
