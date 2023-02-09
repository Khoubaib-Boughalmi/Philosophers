NAME 			= philosophers
BONUS_NAME 		= philosophers_bonus
CFLAGS 			= -Wall -Wextra -Werror
CC 				= cc
RM 				= rm -f

SRCS_MAND=  ./philo/init.c \
			./philo/main.c \
			./philo/parse.c \
			./philo/time.c \
			./philo/utils.c \
			./philo/routine.c \
			./philo/monitor.c 
			
SRCS_BONUS= ./philo_bonus/init.c \
			./philo_bonus/main.c \
			./philo_bonus/parse.c \
			./philo_bonus/time.c \
			./philo_bonus/utils.c \
			./philo_bonus/routine.c \
			./philo_bonus/monitor.c \

M_OBJ 		= ${SRCS_MAND:.c=.o}
B_OBJ 		= ${SRCS_BONUS:.c=.o}

%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

${NAME}: ${M_OBJ}
		${CC} ${CFLAGS} ${M_OBJ} -o ${NAME}

${BONUS_NAME}: ${B_OBJ}
		${CC} ${CFLAGS} ${B_OBJ} -o ${BONUS_NAME}

all:	${NAME} 

bonus:	${BONUS_NAME}

clean:	
		${RM} ${M_OBJ} ${B_OBJ}
	
fclean:	clean
		${RM} ${B_OBJ} ${BONUS_NAME}

re:	fclean all

.PHONY:	all clean fclean re bonus


