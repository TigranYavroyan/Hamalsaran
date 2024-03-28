# $@ represents the target
# $^ represents all the prerequisites
# $< represents the first prerequisite

CC = g++
CFLAGS = -Wall -Wextra -Werror
SRCS = *.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = ./do

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS) : $(SRCS) # The same as %.o : %.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re : fclean all
