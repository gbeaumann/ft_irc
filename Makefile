GTEST_DIR		=	googletest/googletest
INC_DIR			=	inc

SRC_DIR			=	src
SRCS			=	$(SRC_DIR)/main.cpp $(SRC_DIR)/parser.cpp
OBJ_DIR			=	obj
OBJS			=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)
BIN_DIR			=	bin
BIN				=	ft_irc

TST_SRC_DIR		=	tests
TST_SRCS		=	$(TST_SRC_DIR)/test_parser.cpp
TST_OBJ_DIR		=	$(TST_SRC_DIR)/obj
TST_OBJS		=	$(TST_SRCS:%.cpp=$(TST_OBJ_DIR)/%.o)
TST_BIN_DIR		=	$(TST_SRC_DIR)/bin
TST_BIN			=	$(TST_SRCS:$(TST_SRC_DIR)/%.cpp=$(TST_BIN_DIR)/%)

# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS		+=	-isystem $(GTEST_DIR)/include

CXXFLAGS		+=	-g -Wall -Wextra -pthread -std=c++14

GTEST_HEADERS	=	$(GTEST_DIR)/include/gtest/*.h \
					$(GTEST_DIR)/include/gtest/internal/*.h

all: $(BIN)

test: $(TST_BIN)
	for test in $(TST_BIN) ; do ./$$test ; done

.SECONDEXPANSION:

# Compile and link program
$(BIN): $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) $^ -o $(BIN_DIR)/$@

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Compile,link and run tests
$(TST_BIN_DIR)/test_%: $(TST_OBJ_DIR)/test_%.o $(OBJ_DIR)/%.o gtest_main.a | $(TST_BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -lpthread $^ -o $@

# Compile tests
$(TST_OBJ_DIR)/%.o: $(TST_SRC_DIR)/%.cpp $(GTEST_HEADERS) | $(TST_OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $@

$(TST_BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(TST_OBJ_DIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(TST_OBJ_DIR) gtest.a gtest_main.a *.o

fclean: clean
	rm -rf $(BIN) $(TST_BIN_DIR)

############################################

# Builds gtest.a and gtest_main.a.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
