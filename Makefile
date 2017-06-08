PROG		= nibbler

MOD_MENU	= main_menu.so

SRCS		= core/src/main.cpp core/src/GameLoop.cpp

OBJS		= $(SRCS:%.cpp=%.o)

MOD_SRCS	= main_menu/main_menu.cpp

MOD_OBJS	= $(MOD_SRCS:%.cpp=%.o)

CXX			= clang++

INCLUDES	= -I core/include

WFLAGS		= -Wall -Wextra -Werror -g

CXXFLAGS	= $(WFLAGS) $(INCLUDES)

.PHONY: clean fclean re run

all: $(PROG) $(MOD_MENU)

core/src/%.o : core/src/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "\033[01;36m$(PROG) -- \033[00;32m>>\033[0m $@"

$(PROG): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -ldl -o $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mCOMPILED\033[0m"

main_menu/%.o : main_menu/%.cpp
	@$(CXX) $(WFLAGS) -fpic -c $< -o $@
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32m>>\033[0m $@"

$(MOD_MENU): $(MOD_OBJS)
	@$(CXX) -shared -fpic -o $(MOD_MENU) $(MOD_OBJS)
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32mCOMPILED\033[0m"

clean:
	@rm -f $(OBJS)
	@rm -f $(MOD_OBJS)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED OBJECT FILES\033[0m"
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32mREMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(PROG)
	@rm -f $(MOD_MENU)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32mREMOVED SHARED OBJECT\033[0m"

re: fclean all

run:
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@$(MAKE) -s all
	./$(PROG) 640 480
