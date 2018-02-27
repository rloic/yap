YAP - Yet Another Parser
========================

YAP is a library for writing simple automaton-based parsers. It is a trial to make a generic automaton-based parser, motivated by a school lab (CS - INSA Lyon).

# Authors

YAP has been created by:
- Thomas Lacroix (<thomaslacroix@free.fr>)
- Loïc Rouquette (<rouquette.loic@gmail.com>)

for the KALATE Team, CS department - INSA Lyon 2018.


# How to download the library

The library uses GoogleTest for its tests, using git sub-modules. Hence, you have to use one of the following to fetch the GoogleTest sources:

```shell
# Git clone with SSH
git clone --recursive git@gitlab.com:hexanome-kalate/YAP.git

# Git clone with HTTPS
git clone --recursive https://gitlab.com/hexanome-kalate/YAP.git

# If already cloned
git submodule update --init --recursive
```


# How to run the examples

**YAP requires a C++17 compiler, at least GCC 7 or Clang 3.9.**

```shell
# Generate the Makefile using CMake
mkdir build
cd build
cmake ..

# Build and run the example
# make <example_name>
# ./examples/<example_name>/<example_name>
make simple
./examples/simple/simple
```
