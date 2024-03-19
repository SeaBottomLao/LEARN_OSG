project("LEARN_OSG_01")	

set(OSG_DIR "X:")
set(PROJECT_DIR,"X:\LEARN_OSG_01\IncludeH")
set(OSG_DATADIR "X:\OpenSceneGraph-Data")
set(OSG_PLUGIN "C:\temp64\OSG_ENV\bin\osgPlugins-3.6.5")
set(OSG_IMAGE "X:\OpenSceneGraph-Data\Images")
include_directories(${OSG_DIR}/include)
include_directories(${PROJECT_DIR})
link_directories(${OSG_DIR}/lib)

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME} osg2cpp.cpp)
add_executable(${PROJECT_NAME} OsgAnalysis.cpp)
add_executable(${PROJECT_NAME} OsgKeyBoardMouse.cpp)

add_executable(${PROJECT_NAME} stadfx.h)

add_executable(${PROJECT_NAME} WordCoordinate.h)
add_executable(${PROJECT_NAME} CoordinateConvert.h)
add_executable(${PROJECT_NAME} CreateBillBoard.h)
add_executable(${PROJECT_NAME} AutoRotateMode.h)
add_executable(${PROJECT_NAME} ImposerNode.h)
add_executable(${PROJECT_NAME} Occluder.h)
add_executable(${PROJECT_NAME} EarthCoordinate.h)
add_executable(${PROJECT_NAME} CopyOp.h)
add_executable(${PROJECT_NAME} CopyOp2.h)
add_executable(${PROJECT_NAME} CreateQuar.h)
add_executable(${PROJECT_NAME} CreateQuad.h)
add_executable(${PROJECT_NAME} CreateShape.h)
add_executable(${PROJECT_NAME} CreateTesslator.h)
add_executable(${PROJECT_NAME} Simplifier.h)
add_executable(${PROJECT_NAME} Delaunay.h)
add_executable(${PROJECT_NAME} TriStripVisitor.h)

target_link_libraries(${PROJECT_NAME}
	osgd
	osgViewerd
	osgShadowd
	osgTextd
	osgDBd
	osgUtild
	OpenThreadsd
	osgSimd
	osgGAd
)
file(GLOB OSG_DLLS ${OSG_DIR}/bin/*.dll)
file(GLOB OSG_DATAS ${OSG_DATADIR}/*.osg)
file(GLOB OSG_PLUGINS_DLL ${OSG_PLUGIN}/*.dll)
file(GLOB OSG_IMAGE_ALL ${OSG_IMAGE}/*.*)
file(COPY ${OSG_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${OSG_DATAS} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${OSG_PLUGINS_DLL} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${OSG_IMAGE_ALL} DESTINATION ${CMAKE_BINARY_DIR})
# Visual Studio中的调试工作目录（即exe程序内的“./”所指的目录，仅在VS调试中有效）
#set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${ProjectDir}C:\temp64\OSG_ENV\bin")