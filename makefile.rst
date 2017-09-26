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

.. literalinclude:: Makefile
   :start-line: 3 
   :end-line: 6

Creating File Name Lists
========================

We could create names for lists of files we need to either have in the project
code directories, or build as part of constructing the products. But I am lazy,
and I would rather let ``make`` figure those things out. Fortunately, ``make``
has the ability to create lists by looking into your directories to see what is
there. Here is how we build alist of C++ files we need to compile:

.. literalinclude::  Makefile
	:start-line: 3 
	:end-line: 6

