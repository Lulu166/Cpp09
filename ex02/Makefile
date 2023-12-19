NAME			=	PmergeMe

SRC_DIR		=	./srcs/
OBJ_DIR		=	obj/

INCS_DIR	=	includes/
			
MAIN_INC	= -I $(INCS_DIR)
INC			=	$(addprefix $(INCS_DIR), $(LIST_INC))

SRC			=	main.cpp \
				PmergeMe.cpp
				
LIST_INC	=	PmergeMe.hpp \
				PmergeMe.tpp \
				utils.tpp
				
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC				=	c++
CFLAGS			=	-Wall -Wextra -Werror -std=c++98

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(INC)
		@mkdir -p $(OBJ_DIR)
		$(CC) ${CFLAGS} $(MAIN_INC) -o $@ -c $<

$(NAME)		:	$(OBJ) $(INC)
		$(CC) $(CFLAGS) $(OBJ) $(MAIN_INC) -o $(NAME)
					
all			:	$(NAME)

clean		:
		@rm -rf $(OBJ_DIR)

fclean		:	clean
		@rm -rf $(NAME)

re			:	fclean	all

.PHONY		:	all clean fclean re
