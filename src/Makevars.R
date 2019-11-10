# Package-local Makevars
# https://cran.r-project.org/doc/manuals/R-exts.html#Creating-shared-objects
# https://cran.r-project.org/doc/manuals/R-admin.html#Customizing-package-compilation
# PKG_CXXFLAGS = -g3 -O0 -Wall  # does not work (still -g and -O2)
# PKG_CPPFLAGS = -g3 -O0 -Wall  # does not work (still -g and -O2)

# Flags that are already set can be overridden by the environment variable MAKEFLAGS
# MAKEFLAGS="CXXFLAGS = -g3 -O3"   # does not work

# TODO How to inject -g3 -O0 permanently to make this package a base for debugging tutorial?

