========
Makefile
========

This projects ``Makefile`` (received from Professor Roie Black) handles a lot 
of the management details you need to set up a complicated project.


Identifying the build products
==============================

First we need to identify the things we want to build in this project. The major 
program components in this project will be collected into a single library file.

We start the ``Makefile`` by setting up names for the files created (executables 
and archives) in this project::

	# what to build
	USRAPP	:= cpusim
	TSTAPP	:= sim_test
	LIBAR	:= cpusim_lib.a

**cpusim** is the executable name of the main file.  **sim_test** is the executable 
name of the testing files.  **cpusim_lib.a** is the name of the archive file (which 
contains all the ``.o`` files


Creating File Name Lists
========================

We could create names for lists of files we need to either have in the project
code directories, or build as part of constructing the products. But ``make`` 
can do this. Here is how we build the diretory structure we want for our project
and a list of C++ files we need to compile::

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

Project directories are the names of the directories in our project tree (c:/projectname/src, 
etc.). By naming ``SRC`` equal to ``src`` we do not need to change the whole 
file if we need to change the name of our source directory. The same goes for 
all the other directories defined. ``SDIRS`` make sure all these directories 
are created in our project (see below #build any needed directories).

``USRCS``, ``LSRCS`` and ``TSRCS`` defines where and what files to compile.

``UOBJS``, ``LOBJS``, and ``TOBJS`` defines where to put the object files, once 
they are compiled. ``OBJS`` puts the previous places into one variable.


Generating Dependencies Lists
=============================

We do want our program to compile smoothly but some files will not compile 
unless certain items (files) are present. Therefore, we set our dependencies to make
sure things are completed before the next action can happen. ::

	# generate a list of dependencies
	UDEPS	:= $(UOBJS:.o=.d)
	LDEPS	:= $(LOBJS:.o=.d)
	TDEPS	:= $(.OBJS:.o=.d)
	DEPS	:= $(UDEPS) $(LDEPS) $(TDEPS)

****************************** NEED TEXT HERE **********************************************************


Tools and Flags Needed
======================

The tools we want to use are set up as variable, once again so we can change them
in one place as opposed to all over the ``makefile``. ::

	# tools
	CXX	:= g++
	AR	:= ar
	RM	:= rm -f
	PIP	:= pip
	SPHINX	:= sphinx-build
	VENV	:= virtualenv

	CFLAGS	:= -std=c++11 -I $(INC)
	LFLAGS	:= -L $(LIB) $(LIBAR)

``CXX`` is the compiler we want to use. ``AR`` is the archive program to use.  
``RM`` is the command in linux to remove files so we can keep our project 
clean of unnecessary files.  ``PIP``, ``SPHINX`` and ``VENV`` are for Sphinx
documentation which is not being used at this time.  ``CFLAGS`` are the compiling 
flags we want to set in our compile command and ``LFLAGS`` are the linking flags 
we want to set in our compile command.


**Makefile** Rules
==================

Makefile Rules are set up in the following shape (must have tab before recipe)::
	target : prerequisites
		recipe
``make`` will perform the first rule it comes to.  If you want to run a specific 
rule, enter the rule name after ``make``.  Example, ``make run`` will execute the 
``run`` rule below (``.PHONY: run`` keeps ``make`` from doing something with the 
target, usually a file name, named ``run``)::

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

	# build rules for Sphinx documentation
	.PHONY:	install
	install:	docs/_venv
		cd docs && source _venv/bin/activate && \
		$(PIP) install -r requirements.txt && \
		mkdir -p _static && cp ../files/conf.py . && \
		cp ../files/index.rst .

	docs/_venv:
		$(VENV)	docs/_venv

	html:
		cd docs && source _venv/bin/activate && \
		$(SPHINX) -b html -d ../_build/doctrees . ../_build/html

 
``$@`` means left side of ``:`` and ``$^`` means right side of ``:``.
****************************** NEED TEXT HERE **********************************************************


What is this?
=============

what is this? ::

	# include compiler generated dependencies
	-include $(BLD)/*.d

****************************** NEED TEXT HERE **********************************************************
iii



































