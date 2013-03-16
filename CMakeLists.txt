cmake_minimum_required(VERSION 2.8)

PROJECT( ModelKeynes )

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

SET(MARKETMODEL_SOURCE
      src/market.cpp
      src/industrialnode.cpp
      src/bot.cpp
      src/simulationnetwork.cpp
      src/botrandomgaussian.cpp)

ADD_LIBRARY(MarketModel SHARED ${MARKETMODEL_SOURCE})


