cmake_minimum_required(VERSION 3.22)
project(I18n)

add_executable(I18n I18n.c)

add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/ru/LC_MESSAGES/I18n.mo
        COMMAND rm -rf ru && mkdir -p ru/LC_MESSAGES
        COMMAND xgettext -k_ -c ${PROJECT_SOURCE_DIR}/I18n.c -o ${CMAKE_BINARY_DIR}/ru.pot
        COMMAND msgmerge -o ${CMAKE_BINARY_DIR}/ru.po
                ${PROJECT_SOURCE_DIR}/ru.po ${CMAKE_BINARY_DIR}/ru.pot
        COMMAND msgfmt -o ${CMAKE_BINARY_DIR}/ru/LC_MESSAGES/I18n.mo
                ${CMAKE_BINARY_DIR}/ru.po
        DEPENDS ${PROJECT_SOURCE_DIR}/I18n.c
    )

    add_custom_target(translation ALL
        DEPENDS ${CMAKE_BINARY_DIR}/ru/LC_MESSAGES/I18n.mo)

    add_dependencies(I18n translation)
