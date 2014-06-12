# - Try to find Jsonc
# Once done, this will define
#
#  Jsonc_FOUND - system has Jsonc
#  Jsonc_INCLUDE_DIRS - the Jsonc include directories
#  Jsonc_LIBRARIES - link these to use Jsonc

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Jsonc_PKGCONF json-c)
# MacPorts installs "json-c" as "json"
libfind_pkg_check_modules(Json_PKGCONF json)

# Include dir
find_path(Jsonc_INCLUDE_DIR
  NAMES json.h
  PATHS ${Jsonc_PKGCONF_INCLUDE_DIRS} ${Json_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES json-c json
)

# Finally the library itself
find_library(Jsonc_LIBRARY
  NAMES json-c json
  PATHS ${Jsonc_PKGCONF_LIBRARY_DIRS} ${Json_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Jsonc_PROCESS_INCLUDES Jsonc_INCLUDE_DIR)
set(Jsonc_PROCESS_LIBS Jsonc_LIBRARY)
libfind_process(Jsonc)
