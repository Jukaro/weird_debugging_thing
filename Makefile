NAME=	launcher
CC=		clang
SRCS=	$(wildcard srcs/**/*.c)
SRCS+=	$(wildcard srcs/*.c)
OBJS=	$(SRCS:.c=.o)


%.o: %.c
	${CC} -c $< -o $@ -g
	@basename $<

all: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
