if (WIN32)
    list(APPEND LINK_LIB_LIST ${SSL_LIB} ${CRYPTO_LIB})
endif (WIN32)
list(APPEND LINK_LIB_LIST oxf)

INCLUDE_DIRECTORIES("../../include")
INCLUDE_DIRECTORIES("../../src/HttpClient/test")

aux_source_directory(../../src/HttpClient/test CLIENTTEST_DIR)

if (WIN32)
    ADD_DEFINITIONS("-DWIN32_LEAN_AND_MEAN")
endif (WIN32)

add_executable(ClientTest ${CLIENTTEST_DIR})

if (WIN32)
    target_link_libraries(ClientTest ${CMAKE_PROJECT_NAME}Client_static ${LINK_LIB_LIST} Winmm Crypt32)
else (WIN32)
    target_link_libraries(ClientTest ${CMAKE_PROJECT_NAME}Client_static ${LINK_LIB_LIST} ssl crypto uuid pthread dl stdc++ m crypt)
endif (WIN32)
