========
Makefile
========

This projects ``Makefile`` is slightly modified from one received by Roie
Black and it handles a lot of the management details you need to set up a 
complicated project.

Identifying the build products
==============================

The first thing we need to do is identify the things we want to build in this
project. The major program components in this project will be collected into a 
single library file.

We start off this ``Makefile`` by setting up names for these products:

	# what to build
	USRAPP	:= cpusim
	TSTAPP	:= sim_test
	LIBAR	:= cpusim_lib.a

**cpusim** is the executable name of the main file.
**sim_test** is the executable name of the testing files.
**cpusim_lib.a** is the .........

Creating File Name Lists
========================

We could create names for lists of files we need to either have in the project
code directories, or build as part of constructing the products. But ``make`` 
can do this. Here is how we build alist of C++ files we need to compile:

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

need text............



Generating Dependencies Lists
=============================

We do want our program to compile smoothly but some files will not compile 
unless certain items are present. Therefore, we set our dependencies to make
sure things are completed before the next action can happen.

	# generate a list of dependencies
	UDEPS	:= $(UOBJS:.o=.d)
	LDEPS	:= $(LOBJS:.o=.d)
	TDEPS	:= $(.OBJS:.o=.d)
	DEPS	:= $(UDEPS) $(LDEPS) $(TDEPS)

need text............


Tools and Flags Needed
======================

We need tools.......

	# tools
	CXX	:= g++
	AR	:= ar
	RM	:= rm -f

	CFLAGS	:= -std=c++11 -I $(INC)
	LFLAGS	:= -L $(LIB) $(LIBAR)

need text............



**make** Runs Available
=======================

There are several ways to run our Make file depending on what we want to 
accomplish (compiling and running, testing, debugging, cleaning our system).

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

need text............


What is this?
=============

	# include compiler generated dependencies
	-include $(BLD)/*.d

