if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OXF_LIB linuxoxf.a)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OXF_LIB oxf-mt.lib)
endif ()

#oxf
set(OXF_ROOT_PATH ${THIRDPARTY}/Rhapsody/8.4.0/Share/LangCpp)
set(OXF_LIB_PATH ${OXF_ROOT_PATH}/lib/${platform})
if (WIN32)
    set(OXF_INCLUDE_PATH ${OXF_ROOT_PATH}/oxf ${OXF_ROOT_PATH}/osconfig/Win32)
else (WIN32)
    set(OXF_INCLUDE_PATH ${OXF_ROOT_PATH}/oxf ${OXF_ROOT_PATH}/osconfig/Linux)
endif (WIN32)
INCLUDE_DIRECTORIES("${OXF_INCLUDE_PATH}")
set(OXF_LIB ${OXF_LIB_PATH}/${OXF_LIB})
link_directories(${OXF_LIB_PATH})
list(APPEND LINK_LIB_LIST ${OXF_LIB})

INCLUDE_DIRECTORIES("../../include")
INCLUDE_DIRECTORIES("../../src/HttpClient/test")

aux_source_directory(../../src/HttpClient/test CLIENTTEST_DIR)

if (WIN32)
    ADD_DEFINITIONS("-DWIN32_LEAN_AND_MEAN")
endif (WIN32)

add_executable(ClientTest ${CLIENTTEST_DIR})

if (WIN32)
    target_link_libraries(ClientTest ${CMAKE_PROJECT_NAME}Client_static ${LINK_LIB_LIST} Winmm)
else (WIN32)
    target_link_libraries(ClientTest ${CMAKE_PROJECT_NAME}Client_static ${LINK_LIB_LIST} uuid pthread dl stdc++ m crypt)
endif (WIN32)
