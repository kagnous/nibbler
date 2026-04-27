NAME = Nibbler
NAME_BNS = Nibbler_bonus

CPPFLAGS = -Wall -Wextra -Werror -g
CXX = c++
RM = rm -f

SRC_DIR = Src
BNS_DIR = Bonus

OBJDIR = Obj
OBJ_BNSDIR = ObjBns

FILES = nibbler.cpp \
		Game.cpp \
		Snake.cpp

FILES_BNS = nibbler_bns.cpp

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
SRC_BNS = $(addprefix $(BNS_DIR)/, $(FILES_BNS))

OBJ = $(addprefix $(OBJDIR)/, $(FILES:.cpp=.o))
OBJ_BNS = $(addprefix $(OBJ_BNSDIR)/, $(FILES_BNS:.cpp=.o))

all: intro $(NAME)

bonus: intro $(NAME_BNS)

intro:
		@echo "Start building program ...\n"

$(NAME): $(OBJ)
	@echo "\n-----End of compilation-----"
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(NAME_BNS): $(OBJ_BNS)
	@echo "\n-----End of compilation-----"
	@$(CXX) $(CPPFLAGS) $(OBJ_BNS) -o $(NAME_BNS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@echo "Building $@"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_BNSDIR)/%.o: $(BNS_DIR)/%.cpp
	@mkdir -p $(OBJ_BNSDIR)
	@echo "Building $@"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "Suppression des .o ..."
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_BNS)
	@rm -rf $(OBJDIR)
