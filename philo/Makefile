NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror

SRCS = philo.c parser.c utils.c init.c time.c routine.c monitor.c helper.c

HEADS = philo.h

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(FLAGS) $^ -o $@
	@echo "\033[32mMaking Completed✅😜"

$(OBJS) : %.o: %.c $(HEAD) Makefile
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)
	@echo "\033[0;33mCleaning Completed 🧼✨"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[0;31mRemoving Completed 🗑 💔"

re : fclean all

.PHONY : clean	
