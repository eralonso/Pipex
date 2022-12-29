# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 11:59:39 by eralonso          #+#    #+#              #
#    Updated: 2022/12/29 12:24:20 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#<--------------------------------->COLORS<----------------------------------->#
DEF_COLOR	=	\033[1;39m
WHITE_BOLD	=	\033[1m
BLACK		=	\033[1;30m
RED		=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PINK		=	\033[1;35m
CIAN		=	\033[1;36m

#<--------------------------------->NAME<------------------------------------>#
NAME	=	pipex
BONUS	=	pipex

#<-------------------------------->COMANDS<---------------------------------->#
INCLUDE		=	-I ${HEADER}
C_INCLUDE	=	-I ${C_HEADER}
RM		=	rm -rf
MKD		=	mkdir -p
MK		=	Makefile
CFLAGS		=	-Wall -Wextra -Werror

#<--------------------------------->RULES<----------------------------------->#
${OBJ_DIR}%.o	:	%.c ${DEPS_SRCS} ${MK}
	@${MKD} $(dir $@)
	@printf "${PINK}\rCompiling: ${YELLOW}$<...					${DEF_COLOR}\r"
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@

${C_OBJ_DIR}%.o	:	%.c ${DEPS_SRCS} ${MK}
	@${MKD} $(dir $@)
	@printf "${PINK}\rCompiling: ${YELLOW}$<...					${DEF_COLOR}\r"
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${C_INCLUDE} -c $< -o $@

all				:
	@$(MAKE) make_lib
	@$(MAKE) ${NAME}

${NAME}			::	${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -o $@
	@echo "\n${GREEN}Push_swap has been compiled${DEF_COLOR}"

${NAME}			::
	@echo "${YELLOW}Nothing to be done for 'push_swap'${DEF_COLOR}"

bonus			:
	@$(MAKE) make_lib
	@$(MAKE) ${CHECKER}

${CHECKER}		::	${C_OBJS}
	@${CC} ${CFLAGS} ${C_OBJS} ${LIB} -o $@
	@echo "\n${GREEN}Checker has been compiled${DEF_COLOR}"

${CHECKER}		::
	@echo "${YELLOW}Nothing to be done for 'checker'${DEF_COLOR}"
make_lib		:
	@$(MAKE) -C ${LIBRARY}

clean			:
	@$(MAKE) clean -C ${LIBRARY}
	@${RM} ${OBJ_DIR} ${C_OBJ_DIR}
	@echo "${RED}All OBJS && DEPS has been removed${DEF_COLOR}"

fclean			:
	@$(MAKE) clean
	@$(MAKE) fclean -C ${LIBRARY}
	@${RM} ${NAME} ${CHECKER}
	@echo "${RED}Program has been removed${DEF_COLOR}"

re				:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo ""
	@echo "${CIAN}Push_swap has been recompiled${DEF_COLOR}"

.PHONY			: all clean fclean re make_lib bonus

-include		${DEPS}
-include		${C_DEPS}
