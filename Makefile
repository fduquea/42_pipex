# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 13:05:51 by fduque-a          #+#    #+#              #
#    Updated: 2023/07/05 18:01:04 by fduque-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = pipex
SRC = pipex.c
SRC_BONUS = pipex_bonus.c
OBJS = ${SRC:.c=.o}
OBJS_BONUS = ${SRC_BONUS:.c=.o}
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I .
MAKE = make -C
LIBFT_PATH = libft_curr
LIBFT = -L ${LIBFT_PATH} -lft

#valgrind --leak-check=full --trace-children=yes

$(NAME): ${OBJS}
	@ ${MAKE} ${LIBFT_PATH}
	@ ${CC} ${OBJS} ${LIBFT} -o ${NAME}
	@ echo "$(GRAY)*----------------------------------------*$(DEF_COLOR)"
	@ echo "$(GRAY)| $(BLUE)! Compiled pipex program with sucess ! $(GRAY)|$(DEF_COLOR)"
	@ echo "$(GRAY)*----------------------------------------*$(DEF_COLOR)"

all:	${NAME}

bonus: ${OBJS_BONUS}
	@ ${MAKE} ${LIBFT_PATH}
	@ ${CC} ${OBJS_BONUS} ${LIBFT} -o ${NAME}
	@ echo "$(GRAY)*--------------------------------------------------*$(DEF_COLOR)"
	@ echo "$(GRAY)| $(BLUE)! Compiled pipex program with bonus with sucess ! $(GRAY)|$(DEF_COLOR)"
	@ echo "$(GRAY)*--------------------------------------------------*$(DEF_COLOR)"

%.o : %.c 
	@ echo "$(YELLOW)Turning $< into $@$(DEF_COLOR)"
	@ ${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}
	@ echo "$(GREEN)Compiled $< with sucess$(DEF_COLOR)"

clean:
	@ ${MAKE} ${LIBFT_PATH} clean
	@ ${RM} ${OBJS}
	@ ${RM} ${OBJS_BONUS}
	@ echo "$(GRAY)*--------------------------------*$(DEF_COLOR)"
	@ echo "$(GRAY)| $(RED)Removed X pipex object files X $(GRAY)|$(DEF_COLOR)"
	@ echo "$(GRAY)*--------------------------------*$(DEF_COLOR)"

fclean: clean
	@ ${MAKE} ${LIBFT_PATH} fclean
	@ ${RM} ${NAME}
	@ echo "$(GRAY)*-----------------------------------------*$(DEF_COLOR)"
	@ echo "$(GRAY)| $(RED)Removed X 'pipex' program X with sucess $(GRAY)|$(DEF_COLOR)"
	@ echo "$(GRAY)*-----------------------------------------*$(DEF_COLOR)"

re: fclean all
	@ echo "$(GRAY)*--------------------------------------------------*$(DEF_COLOR)"
	@ echo "$(GRAY)| $(RED)X Cleaned X $(YELLOW)and $(GREEN)! Rebuilt ! $(YELLOW)everything for pipex $(GRAY)|$(DEF_COLOR)"
	@ echo "$(GRAY)*--------------------------------------------------*$(DEF_COLOR)"

tests: test_norm
	@echo "\n\n$(GREEN)------WITHOUT FILE PERMISSIONS------$(DEF_COLOR)\n"
	@echo "a a a" > no_permissions.txt
	@chmod 000 no_permissions.txt
	@echo "./pipex no_permissions.txt \"grep a\" \"wc -w\" outfile.txt"
	@echo "\n Shell result:"
	@< no_permissions.txt grep a | wc -w > outfile.txt; echo "Error: $$?"
	@rm -f no_permissions.txt outfile.txt
	@echo "a a a" > no_permissions.txt
	@chmod 000 no_permissions.txt
	@echo "\n Your result:"
	@./pipex no_permissions.txt "grep a" "wc -w" outfile.txt; echo "Error: $$?"
	@echo "\n\n$(GREEN)------WITH FILE PERMISSIONS------$(DEF_COLOR)\n"
	@echo "a a a" > permissions.txt
	@chmod 777 permissions.txt
	@echo "./pipex permissions.txt \"grep a\" \"wc -w\" outfile.txt"
	@echo "\n Shell result:"
	@< permissions.txt grep a | wc -w > outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f permissions.txt outfile.txt
	@echo "a a a" > permissions.txt
	@chmod 777 permissions.txt
	@echo "\n Your result:"
	@./pipex permissions.txt "grep a" "wc -w" outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f permissions.txt outfile.txt
	@echo "\n\n$(GREEN)------TEST N1------$(DEF_COLOR)\n"
	@echo "./pipex infile.txt \"cat\" \"wc -l\" outfile.txt"
	@echo "\n$(YELLOW)WITHOUT INFILE$(DEF_COLOR)\n"
	@echo "Shell result:"
	@< infile.txt cat | wc -l > outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@echo "Your result:"
	@./pipex infile.txt "cat" "wc -l" outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@echo "\n$(YELLOW)WITH INFILE$(DEF_COLOR)\n"
	@echo "ola" > infile.txt
	@echo "Shell result:"
	@< infile.txt cat | wc -l > outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f outfile.txt
	@echo "Your result:"
	@./pipex infile.txt "cat" "wc -l" outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f outfile.txt
	@echo "\n\n$(GREEN)------TEST N2------$(DEF_COLOR)\n"
	@echo "./pipex infile.txt \"grep a1\" \"wc -w\" outfile.txt\n"
	@echo "Shell result:"
	@< infile.txt grep a1 | wc -w > outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f outfile.txt
	@echo "Your result:"
	@./pipex infile.txt "grep a1" "wc -w" outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f outfile.txt infile.txt
	@echo "\n\n$(GREEN)------TEST N3------$(DEF_COLOR)\n"
	@echo "./pipex infile.txt \"grep a1\" \"LOL -w\" outfile.txt\n"
	@echo "Shell result:"
	@< infile.txt grep a1 | LOL -w > outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f outfile.txt
	@echo "Your result:"
	@./pipex infile.txt "grep a1" "LOL -w" outfile.txt; echo "Error: $$?"
	@cat outfile.txt | cat -e
	@rm -f outfile.txt no_permissions.txt

# check the norm
test_norm:
	@rm -f infile infile.txt outfile outfile.txt no_permissions.txt
	@echo "\n\n$(GREEN)------NORM ERRORS------$(DEF_COLOR)"
	@norminette | grep Error

# test the mandatory part with existing infile, good rights and existing commands
test_m_basic:

# test that mandatory only takes 4 arguments (argc = 5)
test_m_arguments:

# test the mandatory part with existing infile, bad rights and existing commands
test_m_file_permissions:

# test the mandatory part with no infile, good rights and existing commands
test_m_no_infile:

# test the mandatory part with existing infile, good rights and bad commands
test_m_bad_command:

# test the mandatory part with no infile, bad infile rights and bad commands
test_m_no_rights_and_bad_command:

# test the mandatory part with no infile, bad rights and bad commands
test_m_no_file_and_bad_command:

# create the bonus part
test_bonus: bonus

# test the bonus part with existing infile, good rights and existing commands
test_b_basic:

test_b_arguments:

test_b_file_permissions:

test_b_no_infile:

test_b_bad_command:

test_b_no_file_and_bad_command:

test_b_alot_arguments:

test_b_heredoc:

.PHONY: all clean fclean re bonus unit_tests