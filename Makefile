# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 11:59:39 by eralonso          #+#    #+#              #
#    Updated: 2023/01/13 14:28:47 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#<--------------------------------->COLORS<----------------------------------->#
DEF_COLOR	=	\033[1;99m
WHITE_BOLD	=	\033[1m
BLACK		=	\033[1;90m
RED			=	\033[1;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[1;94m
PINK		=	\033[1;95m
CIAN		=	\033[1;96m

#<--------------------------------->NAME<------------------------------------>#
NAME		=	pipex
BONUS		=	pipex_bonus

#<-------------------------------->LIBRARY<---------------------------------->#
LIBRARY		=	lib/
LIB			=	lib/lib.a

#<-------------------------------->HEADERS<---------------------------------->#
HEADER		=	./includes/
B_HEADER	=	./bonus/inc/

#<--------------------------------->DIRS<------------------------------------>#
SRC_DIR		=	sources/
OBJ_DIR		=	objs/

B_SRC_DIR	=	bonus/src/
B_OBJ_DIR	=	bonus/objs/

#<--------------------------------->FILES<---------------------------------->#
FILES		=	pipex ft_utils ft_comand

B_FILES		=	pipex_bonus

#<--------------------------------->SRCS<----------------------------------->#
SRCS		=	$(addprefix ${SRC_DIR}, $(addsuffix .c, ${FILES}))

B_SRCS		=	$(addprefix ${B_SRC_DIR}, $(addsuffix .c, ${B_FILES}))

#<----------------------------->OBJS && DEPS<------------------------------->#
OBJS		=	$(addprefix ${OBJ_DIR}, ${SRCS:.c=.o})
DEPS		=	${OBJS:.o=.d}

B_OBJS		=	$(addprefix ${B_OBJ_DIR}, ${B_SRCS:.c=.o})
B_DEPS		=	${B_OBJS:.o=.d}

DEPS_SRCS	=	lib/*/objs/src/*/*.o

#<-------------------------------->COMANDS<---------------------------------->#
INCLUDE		=	-I ${HEADER}
B_INCLUDE	=	-I ${B_HEADER}
RM			=	rm -rf
MKD			=	mkdir -p
MK			=	Makefile
CFLAGS		=	-Wall -Wextra -Werror

#<--------------------------------->RULES<----------------------------------->#
${OBJ_DIR}%.o	:	%.c ${DEPS_SRCS} ${MK}
	@${MKD} $(dir $@)
	@printf "${PINK}\rCompiling: ${YELLOW}$<...					${DEF_COLOR}\r"
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@

${B_OBJ_DIR}%.o	:	%.c ${DEPS_SRCS} ${MK}
	@${MKD} $(dir $@)
	@printf "${PINK}\rCompiling: ${YELLOW}$<...					${DEF_COLOR}\r"
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${B_INCLUDE} -c $< -o $@

all				:
	@$(MAKE) -C ${LIBRARY}
	@$(MAKE) ${NAME}

${NAME}			::	${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -o $@
	@echo "\n${GREEN}Pipex has been compiled${DEF_COLOR}"

${NAME}			::
	@echo "${YELLOW}Nothing to be done for 'pipex'${DEF_COLOR}"

bonus			:
	@$(MAKE) -C ${LIBRARY}
	@$(MAKE) ${CHECKER}

${BONUS}		::	${B_OBJS}
	@${CC} ${CFLAGS} ${B_OBJS} ${LIB} -o $@
	@echo "\n${GREEN}Pipex bonus has been compiled${DEF_COLOR}"

${BONUS}		::
	@echo "${YELLOW}Nothing to be done for 'pipex bonus'${DEF_COLOR}"

clean			:
	@$(MAKE) clean -C ${LIBRARY}
	@${RM} ${OBJ_DIR} ${B_OBJ_DIR}
	@echo "${RED}All OBJS && DEPS has been removed${DEF_COLOR}"

fclean			:
	@$(MAKE) clean
	@$(MAKE) fclean -C ${LIBRARY}
	@${RM} ${NAME} ${BONUS}
	@echo "${RED}Program has been removed${DEF_COLOR}"

re				:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo ""
	@echo "${CIAN}Pipex has been recompiled${DEF_COLOR}"

.PHONY			: all clean fclean re bonus

-include		${DEPS}
-include		${B_DEPS}
