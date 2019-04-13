program_NAME := MultiUser-Chat1
program_CXX_HEADERS := $(../HEADERS1/wildcard	*.hpp)
program_C_SRCS := $(wildcard *.c)
program_CXX_SRCS = $(wildcard *.cpp)
program_CXX_SRC = $(wildcard *.hpp)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o} ${program_CXX_SRC:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_INCLUDE_DIRS := ../Headers
program_LIBRARY_DIRS :=
program_LIBRARIES :=
CPPFLAGS +=	$(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS +=	$(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS +=	$(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all clean distclean

all:	$(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME) -pthread

clean:
	rm -f $(program_NAME)
	rm -f	$(program_OBJS)

distclean: clean
