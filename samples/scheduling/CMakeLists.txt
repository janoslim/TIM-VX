message("samples/scheduling")

set(TARGET_NAME "scheduling")

aux_source_directory(. SRC)
aux_source_directory(./parser PARSER)
aux_source_directory(./builder BUILDER)
aux_source_directory(./model MODEL)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(./)
include_directories(./parser)
include_directories(./builder)
include_directories(./model)

add_executable(${TARGET_NAME} ${SRC} ${PARSER} ${BUILDER} ${MODEL})
target_link_libraries(${TARGET_NAME} ${OVXDRV_LIBRARIES}  tim-vx-static)