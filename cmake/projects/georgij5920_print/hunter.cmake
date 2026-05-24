# Example of a custom Hunter package recipe for the educational print library.
# In a real package registry this file would contain hunter_download() with
# URL/SHA1 of the released archive. The project keeps the recipe here to show
# the required package layout for the lab08 homework task.

include(hunter_add_version)
include(hunter_configuration_types)
include(hunter_download)

hunter_add_version(
  PACKAGE_NAME georgij5920_print
  VERSION 0.1.0
  URL "https://github.com/georgij5920/lab08/archive/refs/tags/v0.1.0.tar.gz"
  SHA1 "0000000000000000000000000000000000000000"
)

hunter_configuration_types(georgij5920_print CONFIGURATION_TYPES Release)
hunter_download(PACKAGE_NAME georgij5920_print)
