# - Try to find Uuid
# Once done, this will define
#
#  Uuid_FOUND - system has Uuid
#  Uuid_INCLUDE_DIRS - the Uuid include directories
#  Uuid_LIBRARIES - link these to use Uuid

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Uuid_PKGCONF uuid)

# Include dir
find_path(Uuid_INCLUDE_DIR
  NAMES uuid.h
  PATHS ${Uuid_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES uuid
)

# Finally the library itself
find_library(Uuid_LIBRARY
  NAMES uuid
  PATHS ${Uuid_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Uuid_PROCESS_INCLUDES Uuid_INCLUDE_DIR)
set(Uuid_PROCESS_LIBS Uuid_LIBRARY)
libfind_process(Uuid)
