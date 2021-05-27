#set(Boost_NO_SYSTEM_PATHS TRUE)
#if (Boost_NO_SYSTEM_PATHS)
#  set(BOOST_ROOT "/usr/local")
#  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include/boost_1_73_0")
#  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/include/boost_1_73_0/stage/lib")
#endif (Boost_NO_SYSTEM_PATHS)
#find_package(Boost REQUIRED beast )
#include_directories(${BOOST_INCLUDE_DIRS})


find_package(OpenSSL REQUIRED)

#list(APPEND CUDA_NVCC_FLAGS "--compiler-options -fPIC")


add_compile_options(-fPIC)

add_executable(webInterface     cpp/main.cpp
                                cpp/http_session.cpp
                                cpp/listener.cpp
                                cpp/shared_state.cpp
                                cpp/websocket_session.cpp
                                cpp/webInterface.cpp
                                cpp/algValidator.cpp
                                #cpp/jwt.cpp
                                #cpp/base64.cpp
                                cpp/message.cpp
                                cpp/session.cpp)

#add_library(webInterface STATIC
#                              cpp/http_session.cpp
#                              cpp/listener.cpp
#                              cpp/shared_state.cpp
#                             cpp/websocket_session.cpp
#                              cpp/webInterface.cpp
#                              cpp/algValidator.cpp
#                              cpp/jwt.cpp
#                              cpp/base64.cpp
#                              cpp/session.cpp)


target_link_libraries(webInterface PRIVATE project_warnings project_options
                      OpenSSL::SSL)

target_include_directories(webInterface PRIVATE project_warnings project_options 
                           ${PROJECT_SOURCE_DIR}/include/WebInterface
                           /usr/local/ssl/include/openssl
                           )


