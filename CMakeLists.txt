cmake_minimum_required(VERSION 3.8)

project (
 "CppInternationalization"
 VERSION 1.0.0
 LANGUAGES CXX
)

add_executable(${PROJECT_NAME} "main.cpp")

# add libintl

find_package(Intl REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ${Intl_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC ${Intl_INCLUDE_DIRS})

# setup gettext

set(GETTEXT_DOMAIN "my-domain")
set(GETTEXT_TARGET "gettext-target")
set(GETTEXT_OUTPUT_DIR "locales")
set(GETTEXT_LANGUAGES "en" "de" "pl")

target_compile_definitions(${PROJECT_NAME} PUBLIC "GETTEXT_DOMAIN=\"${GETTEXT_DOMAIN}\"")
target_compile_definitions(${PROJECT_NAME} PUBLIC "GETTEXT_OUTPUT_DIR=\"${GETTEXT_OUTPUT_DIR}\"")


include("extern/gettext-cmake/Gettext_helpers.cmake")
CONFIGURE_GETTEXT(
 DOMAIN ${GETTEXT_DOMAIN}
 TARGET_NAME ${GETTEXT_TARGET}
 SOURCES "main.cpp"
 POTFILE_DESTINATION ${GETTEXT_OUTPUT_DIR}
 XGETTEXT_ARGS
  "--keyword=_"
  "--add-comments=TRANSLATORS:"
  "--package-name=${PROJECT_NAME}"
  "--package-version=${PROJECT_VERSION}"
  "--msgid-bugs-address=https://github.com/erri120/${PROJECT_NAME}/issues"
  "--copyright-holder=erri120"
 LANGUAGES ${GETTEXT_LANGUAGES}
 BUILD_DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>/${GETTEXT_OUTPUT_DIR}
 ALL
)
