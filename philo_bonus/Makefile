NAME = philo_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror

SRCS = philo_bonus.c parser_bonus.c utils_bonus.c init_bonus.c time_bonus.c routine_bonus.c helper_bonus.c  utils_bonus1.c monitor_bonus.c

HEADS = philo_bonus.h

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(FLAGS) $^ -o $@
	@echo "\033[32mMaking Bonus Completed✅😜"

$(OBJS) : %.o: %.c $(HEADS) Makefile
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)
	@echo "\033[0;33mCleaning Completed 🧼✨"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[0;31mRemoving Completed 🗑 💔"

re : fclean all

.PHONY : clean