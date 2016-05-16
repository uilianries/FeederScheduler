cmake_minimum_required(VERSION 2.8)
project(feeder_scheduler CXX)

find_library(IOTMQTTCLIENTLIB IoTMQTTClient)
find_library(PAHOLIB Paho)
find_library(POCOFOUNDATIONLIB PocoFoundation)
find_library(POCOUTILLIB PocoUtil)
find_library(POCOJSONLIB PocoJSON)
find_library(PTHREADLIB pthread)
find_library(SSLLIB ssl)
find_library(CRYPTOLIB crypto)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wshadow -Wextra")

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${IOTMQTTCLIENTLIB} ${PAHOLIB} ${PTHREADLIB} ${SSLLIB} ${CRYPTOLIB} ${POCOFOUNDATIONLIB} ${POCOUTILLIB} ${POCOJSONLIB} )

install(TARGETS ${CMAKE_PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

install(FILES script/smartaquarium-feeder-scheduler.sh
        DESTINATION /etc/init.d
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)