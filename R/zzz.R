# ***************************************************************************
# Copyright (C) 2016 Juergen Altfeld (R@altfeld-im.de)
# ---------------------------------------------------------------------------
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************


# We need to import something (anything) from Rcpp so that internal Rcpp code is properly loaded. This is a bug in R and hopefully will be fixed in the future.

#' @importFrom Rcpp sourceCpp
#' @useDynLib CppDebugHelper
"_PACKAGE"



# clean-up
.onUnload <- function (libpath) {
  gc()
  library.dynam.unload("CppDebugHelper", libpath)   # http://r-pkgs.had.co.nz/src.html
}
