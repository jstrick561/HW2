# Makefile for CPUsim

# what to build
USRAPP	:= cpusim
TSTAPP	:= sim_test
LIBAR	:= cpusim_lib.a

# project directories
SRC		:=	src
LIB		:=	lib
TST		:=	tests
DOC		:=	docs
INC		:=	include
BLD		:=	_build

DIRS 	:=	$(SRC) $(LIB) $(TST) $(DOC) $(INC) \
		$(BLD) $(BLD)/$(SRC) $(BLD)/$(LIB) $(BLD)/$(TST)

USRCS = $(wildcard $(SRC)/*.cpp)
LSRCS = $(wildcard $(LIB)/*.cpp)
TSRCS = $(wildcard $(TST)/*.cpp)

UOBJS = $(USRCS:%.cpp=$(BLD)/%.o)
LOBJS = $(LSRCS:%.cpp=$(BLD)/%.o)
TOBJS = $(TSRCS:%.cpp=$(BLD)/%.o)
OBJS  = $(UOBJS) $(LOBJS) $(TOBJS)

# generate a list of dependencies
UDEPS	:= $(UOBJS:.o=.d)
LDEPS	:= $(LOBJS:.o=.d)
TDEPS	:= $(.OBJS:.o=.d)
DEPS	:= $(UDEPS) $(LDEPS) $(TDEPS)

# tools
CXX	:= g++
AR	:= ar
RM	:= RM -f

CFLAGS	:= -std=c++11 -I $(INC)
LFLAGS	:= -L $(LIB) $(LIBAR)

# targets follow ----------------------

.PHONY: all
all:	directories $(USRAPP) $(TSTAPP)

.PHONY:	run
run:	$(USRAPP)
	./$(USRAPP)

.PHONY: test
test:	$(TSTAPP)
	./$(TSTAPP)

$(USRAPP):	$(UOBJS) $(LIBAR)
	$(CXX) $(LFLAGS) -o $@ $^ 

$(TSTAPP):	$(TOBJS) $(LIBAR)
	$(CXX) $(LFLAGS) -o $@ $^

$(LIBAR):	$(LOBJS)
	$(AR) rcs $@ $^

# build any needed directories
.PHONY:	directories
directories: $(DIRS)

$(DIRS):
	mkdir -p $@

# inplicit rule to build object files
$(BLD)/%.o:	%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ -MMD -MP

.PHONY:	clean
clean:
	$(RM) $(USRAPP) $(TSTAPP) $(OBJS) $(DEPS)

# show file lists
.PHONY: debug
debug:
	-@echo USRCS = $(USRCS)
	-@echo LSRCS = $(LSRCS)
	-@echo TSRCS = $(TSRCS)
	-@echo UOBJS = $(UOBJS)
	-@echo LOBJS = $(LOBJS)
	-@echo TOBJS = $(TOBJS)
	-@echo UDEPS = $(UDEPS)
	-@echo LDEPS = $(LDEPS)
	-@echo TDEPS = $(TDEPS)
	-@echo DIRS  = $(DIRS)

# include compiler generated dependencies
-include $(BLD)/*.d

