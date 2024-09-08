cmake_minimum_required(VERSION 3.22)
project(lab6_7)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")




add_executable(lab6_7 main.cpp
        repos/repository.cpp
        repos/repository.h
        business/service.cpp
        business/service.h
        interface/ui.cpp
        interface/ui.h
        domain/activity.cpp
        domain/activity.h
        except/Exceptions.cpp
        except/Exceptions.h
        utils/vector.h
        cmake-build-debug/test_current_activities.txt
        utils/export.h
        utils/export.cpp
        repos/currentActivities.h
        repos/currentActivities.cpp
        business/undo.h
        interface/activityGUI.h
        interface/activityGUI.h
        interface/activityGUI.cpp
        interface/activityGUI.cpp
        utils/Observer.cpp
        utils/Observer.h
        utils/MyTableModel.h
)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
target_link_libraries(lab6_7 Qt6::Widgets)