# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 12:28:57 by mmarinel          #+#    #+#              #
#    Updated: 2022/06/22 17:52:05 by mmarinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SAY = say
#NORMINETTE = norminette -R CheckForbiddenSourceHeader
CC = @gcc
#HOME = /Users/mmarinel
CFLAGS = -I -Wall -Werror -Wextra -fsanitize=address -static-libsan -g
READLINE_FLAGS = -L/usr/include -lreadline -L/Users/mmarinel/.brew/opt/readline/lib -I /Users/mmarinel/.brew/opt/readline/include

MANDATORY_OBJS = $(shell find . -name "*.c" -print | grep -v bonus.c | sed 's/\.c/\.o/g')
BONUS_OBJS = $(shell find . -name "*.c" -print | grep -v mand | sed 's/\.c/\.o/g')


####################### Unvoiced Makes #########################
all:
	@$(MAKE) .ADD_MANDATORY SAY="say -o /dev/null"
bonus:
	@$(MAKE) .ADD_BONUS SAY="say -o /dev/null"
norm:
	@$(MAKE) n SAY="say -o /dev/null"
clean:
	@$(MAKE) cl SAY="say -o /dev/null"
fclean:
	@$(MAKE) fcl SAY="say -o /dev/null"

####################### VOCAL ASSISTANT #########################
say: .ADD_MANDATORY
bonus_say: .ADD_BONUS
norm_say: n
clean_say: cl
fclean_say: fcl
re_say: fclean_say say
re_bonus_say: fclean_say bonus_say


####################### NORMINETTE #########################
# NORM_ERRS = 
# ifndef final_msg
# 	ifeq ($(shell test $(shell norminette -R CheckForbiddenSourceHeader | grep Error: | wc -l) -gt 0; echo $$?), 0)
# 			final_msg = "My disappointment is immeasurable and my day is ruined"
# 			final_msg_voice = Karen
# 			norm_fail = $(shell norminette -R CheckForbiddenSourceHeader | grep Error: | wc -l)
# 			ifeq (test $(shell norminette -R CheckForbiddenSourceHeader | grep Error: | wc -l) -gt 1; echo $$?, 0)
# 				norm_fail += " Norm Errors found!"
# 			else
# 				norm_fail += " Norm Error found!"
# 			endif
# 	else
# 		final_msg = "Good Job, GG, you are a piece of shit"
# 		final_msg_voice = Karen
# 		norm_success = $(shell echo "No Norm Errors found!")
# 	endif 
# endif


####################### CORE #######################################
do_bonus: $(NAME)
do_mandatory: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) $(OBJS) -o $(NAME)

cl:
	@printf "removing Object files...\n"
	@/bin/rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@printf "\033[0;35mObject files removed!\n"
	@echo "\033[0;37m"

fcl: cl
	@printf "removing program executable...\n"
	@/bin/rm -f ./minishell
	@printf "\033[0;35mExecutable removed!\n"
	@echo "\033[0;37m"

re: fclean all

re_bonus: fclean bonus

.ADD_MANDATORY:
	@printf "\033[0;36mMaking Mandatory part\n"
	@echo "\033[0;37m"
	@$(MAKE) do_mandatory OBJS="$(MANDATORY_OBJS)" NAME="minishell"

.ADD_BONUS:
	@printf "\033[1;36mMaking Bonus part\n"
	@echo "\033[0;37m"
	@$(MAKE) do_bonus OBJS="$(BONUS_OBJS)" NAME="minishell"

