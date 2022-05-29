cmake_minimum_required(VERSION 3.19)

find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
  message(WARNING "Doxygen not found. Skipping building documentation.")
  return()
endif()

set(DOXYGEN_QUIET YES)

set(DOXYGEN_AUTOLINK_SUPPORT NO)
set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_FULL_PATH_NAMES NO)
set(DOXYGEN_EXTRACT_ALL YES)

if(CHIMP_BUILD_INTERNAL_DOC)
  set(DOXYGEN_EXTRACT_PRIVATE YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
endif()

set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_DOT_TRANSPARENT YES)

set(DOXYGEN_HTML_HEADER header.html)
set(DOXYGEN_HTML_EXTRA_FILES
  doxygen-awesome-css/doxygen-awesome-darkmode-toggle.js
  doxygen-awesome-css/doxygen-awesome-paragraph-link.js
  doxygen-awesome-css/doxygen-awesome-fragment-copy-button.js
)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_HTML_EXTRA_STYLESHEET doxygen-awesome-css/doxygen-awesome.css)

doxygen_add_docs(chimp_doc
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ALL
)
