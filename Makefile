NAME = Nibbler
NAME_BNS = Nibbler_bonus
LIB_NCURSES = libncurses_display.so
LIB_SDL = libsdl_display.so
LIB_SFML = libsfml_display.so

CPPFLAGS = -Wall -Wextra -Werror -g
LDLIBS = -ldl
CXX = c++
RM = rm -f
SFML_CFLAGS = $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
SFML_LIBS   = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

SRC_DIR = Src
BNS_DIR = Bonus

OBJDIR = Obj
OBJ_BNSDIR = ObjBns

FILES = Nibbler.cpp \
		Game.cpp \
		Snake.cpp 

FILES_BNS = Nibbler_bns.cpp \
			Game_bns.cpp \
			Snake_bns.cpp

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
SRC_BNS = $(addprefix $(BNS_DIR)/, $(FILES_BNS))

OBJ = $(addprefix $(OBJDIR)/, $(FILES:.cpp=.o))
OBJ_BNS = $(addprefix $(OBJ_BNSDIR)/, $(FILES_BNS:.cpp=.o))

all: intro $(LIB_NCURSES) $(LIB_SDL) $(LIB_SFML) $(NAME)

bonus: intro $(LIB_NCURSES) $(LIB_SDL) $(LIB_SFML) $(NAME_BNS)

intro:
		@echo "Start building program ...\n"

$(NAME): $(OBJ)
	@echo "\n-----End of compilation-----"
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LDLIBS)

$(LIB_NCURSES): $(OBJDIR)/NcursesDisplay.o
	$(CXX) $(CPPFLAGS) -fPIC -shared $(OBJDIR)/NcursesDisplay.o -o $(LIB_NCURSES) -lncursesw

$(LIB_SDL): $(OBJDIR)/SdlDisplay.o
	$(CXX) -shared -fPIC $< -o $@ -lSDL2

$(LIB_SFML): $(OBJDIR)/SfmlDisplay.o
	$(CXX) -shared -fPIC $< -o $@ $(SFML_LIBS) -Wl,-rpath,$(PWD)/build_check/install/lib

$(NAME_BNS): $(OBJ_BNS)
	@echo "\n-----End of compilation-----"
	@$(CXX) $(CPPFLAGS) $(OBJ_BNS) -o $(NAME_BNS) $(LDLIBS)

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

$(OBJDIR)/SfmlDisplay.o: $(SRC_DIR)/SfmlDisplay.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -fPIC $(SFML_CFLAGS) -c $< -o $@

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
	$(RM) $(LIB_SFML)

re: fclean all

.PHONY: all bonus intro clean fclean re
