NAME= philo

SRC = actions.c  creat.c  free.c  main.c  parsing.c  time_print.c

CC      = clang

#FSAN = -fsanitize=address -fsanitize=leak -fsanitize=undefined
#FSAN = -fsanitize=thread

CFLAGS	= -Werror -Wextra -Werror -g3 $(FSAN)
LFLAGS	= -lpthread -g3 $(FSAN)

OBJ = $(SRC:.c=.o)


${NAME}: ${OBJ} 
	$(CC) $(OBJ) $(LFLAGS) -o $@

#malloc_test: $(OBJ)
#$(CC) -fsanitize=undefined -rdynamic -o $@ ${OBJ} $(LFLAGS) -L. -lmallocator

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

clean: 
	rm -f $(OBJ) 

fclean: clean
	${RM} ${NAME}
	

re: fclean all

.PHONY : all clean fclean re 
