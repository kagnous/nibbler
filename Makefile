NAME = Nibbler
NAME_BNS = Nibbler_bonus
LIB_NCURSES = libncurses_display.so
LIB_SDL = libsdl_display.so

CPPFLAGS = -Wall -Wextra -Werror -g
CXX = c++
RM = rm -f

SRC_DIR = Src
BNS_DIR = Bonus

OBJDIR = Obj
OBJ_BNSDIR = ObjBns

FILES = Nibbler.cpp \
		Game.cpp \
		Snake.cpp 

FILES_BNS = nibbler_bns.cpp

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
SRC_BNS = $(addprefix $(BNS_DIR)/, $(FILES_BNS))

LIB_SRC = $(SRC_DIR)/NcursesDisplay.cpp
LIB_OBJ = $(OBJDIR)/NcursesDisplay.o

OBJ = $(addprefix $(OBJDIR)/, $(FILES:.cpp=.o))
OBJ_BNS = $(addprefix $(OBJ_BNSDIR)/, $(FILES_BNS:.cpp=.o))

all: intro $(LIB_NCURSES) $(LIB_SDL) $(NAME)

bonus: intro $(NAME_BNS)

intro:
		@echo "Start building program ...\n"

$(NAME): $(OBJ)
	@echo "\n-----End of compilation-----"
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(LIB_NCURSES): $(LIB_OBJ)
	$(CXX) $(CPPFLAGS) -fPIC -shared $(LIB_OBJ) -o $(LIB_NCURSES) -lncurses

$(LIB_SDL): $(OBJDIR)/SdlDisplay.o
	$(CXX) -shared -fPIC $< -o $@ -lSDL2

$(NAME_BNS): $(OBJ_BNS)
	@echo "\n-----End of compilation-----"
	@$(CXX) $(CPPFLAGS) $(OBJ_BNS) -o $(NAME_BNS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@echo "Building $@"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/NcursesDisplay.o: $(SRC_DIR)/NcursesDisplay.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -fPIC -c $< -o $@

$(OBJDIR)/SdlDisplay.o: $(SRC_DIR)/SdlDisplay.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -fPIC -c $< -o $@

$(OBJ_BNSDIR)/%.o: $(BNS_DIR)/%.cpp
	@mkdir -p $(OBJ_BNSDIR)
	@echo "Building $@"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "Suppression des .o ..."
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_BNS)
	@rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BNS)
	$(RM) $(LIB_NCURSES)
	$(RM) $(LIB_SDL)

re: fclean all

.PHONY: all bonus intro clean fclean re
