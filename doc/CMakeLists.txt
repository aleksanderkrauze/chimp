cmake_minimum_required(VERSION 3.12)

find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
  message(WARNING "Doxygen not found. Skipping building documentation.")
  return()
endif()

set(DOXYGEN_QUIET YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_FULL_PATH_NAMES NO)

set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_DOT_TRANSPARENT YES)

set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_HTML_EXTRA_STYLESHEET doxygen-awesome-css/doxygen-awesome.css)

doxygen_add_docs(chimp_doc
  ${PROJECT_SOURCE_DIR}/include ALL
)