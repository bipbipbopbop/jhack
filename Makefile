LIB_NAME := jhack

# Basic definitions
SRC_PATH := source
OBJ_PATH := .bin

## Target definition
NAME := $(LIB_NAME).lib


# Compiler
CC := g++
CCFLAGS := -std=c++14 -Wall -Werror -Wextra


# Commands
RM := rm -f
RMDIR := rm -Rdf
MKDIR := mkdir -p


# Source files
SRC_NAME :=	jhack.cpp


SRC := $(addprefix $(SRC_PATH)/, $(SRC))
OBJ := $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

OBJ_DIRS := $(sort $(dir $(OBJ)))

# Rules
all: $(NAME)

#$(LIB_NAME): $(NAME)
#	ln -fs $< $@

$(NAME): $(OBJ_DIRS) $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

$(OBJ_DIRS):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(addprefix $(SRC_PATH)/, %.cpp)
	$(CC) $(CCFLAGS) -MMD -MF $(<:.cpp=.d) -c $< -o $@


# Prerequisites files
DEP_FILES = $(SRC:%.cpp=%.d)
-include $(DEP_FILES)


clean:
	$(RM) $(OBJ)
	$(RM) $(DEP_FILES)
	$(RMDIR) $(OBJ_DIRS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Test Makefile
include test.mk

.PHONY: all clean fclean re test
