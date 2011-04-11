# Copyright 2011 Marco Ribeiro
# Author: Marco Ribeiro
# E-mail: marcotcr@gmail.com

# Make sure the compiler can find include from our libraries.
INCLUDE_DIRECTORIES(${RI_SOURCE_DIR}/src/RICPlib)
INCLUDE_DIRECTORIES(${RI_SOURCE_DIR}/src/util)
INCLUDE_DIRECTORIES(${RI_SOURCE_DIR}/src/)

# Add binary called "ircpReader" that is built from the source file "testReader.cc"
ADD_EXECUTABLE(teste test_reader ../src/inverted_index
../src/term_document_frequency ../src/query_processor ../src/compressor)

# Link the executable to the necessary libraries.
TARGET_LINK_LIBRARIES(teste RICPlib z htmlcxx util iconv)
