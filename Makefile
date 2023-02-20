NAME = 	webserv
CFLAGS = -Wall -Wextra -Werror
CC = c++

##################################
CONFIG_FILES	=	./parser/modules/config-data/config.class.cpp 
CONFIG_HEADERS	=	./parser/modules/config-data/config.class.hpp \

LOCATION =	./parser/modules/location/location.class.cpp
LOCATION_HEADERS =	./parser/modules/location/location.class.hpp

DESCENT_PARSER	=	./parser/modules/descent-parser/parse.config.cpp
DESCENT_PARSER_HEADERS =	./parser/modules/descent-parser/parse.config.hpp

UTILS	=	./parser/modules/utils/utils.cpp
UTILS_HEADERS =	./parser/modules/utils/utils.hpp

HEADERS	= $(CONFIG_HEADERS) $(LOCATION_HEADERS) $(DESCENT_PARSER_HEADERS) $(UTILS_HEADERS) ./parser/parser.hpp ./general_info.hpp ./server/server.hpp ./server/socket.hpp ./request_response/request_response.hpp ./server/requestData.hpp

##################################

SRCS = main.cpp ./server/server.cpp  ./server/socket.cpp ./request_response/request_response.cpp ./server/requestData.cpp ./request_response/chunked_decoder.cpp \
		$(CONFIG_FILES) $(LOCATION) $(DESCENT_PARSER) $(UTILS)
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

%.o:%.cpp 
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all