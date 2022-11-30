NAME	= descent

CONFIG_FILES	=	modules/config-data/config.class.cpp \
								modules/config-data/config.utils.cpp
CONFIG_HEADERS	=	modules/config-data/config.class.hpp \
								modules/config-data/config.utils.hpp

LOCATION =	modules/location/location.class.cpp \
						modules/location/location.utils.cpp
LOCATION_HEADERS =	modules/location/location.class.hpp

DESCENT_PARSER	=	modules/descent-parser/parse.config.cpp
DESCENT_PARSER_HEADERS =	modules/descent-parser/parse.config.hpp

SRC		= $(CONFIG_FILES) $(LOCATION) $(DESCENT_PARSER) main.cpp
OBJ		= $(addprefix obj/, $(SRC:.cpp=.o))

CC		= c++

HEADERS	= $(CONFIG_HEADERS) $(LOCATION_HEADERS) $(DESCENT_PARSER_HEADERS)

$(NAME)	: $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(NAME)

obj/%.o : %.cpp
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c -o $@ $<

all		: $(NAME)

clean	: 
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all