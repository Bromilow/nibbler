PROG		= nibbler

SRCS		= $(shell find -name "*.cpp")

OBJS		= $(SRCS:%.cpp=%.o)

CXX			= clang++

CXXFLAGS	= -Wall -Wextra -Werror -g

.PHONY: clean fclean re run

all: $(PROG)

%.o : %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "\033[01;36m$(PROG) -- \033[00;32m>>\033[0m $@"

$(PROG): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mCOMPILED\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"

re: fclean all

run:
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@$(MAKE) -s all
