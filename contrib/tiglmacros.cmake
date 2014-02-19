function(AddToCheckstyle)
  if(PYTHONINTERP_FOUND)
    get_filename_component(dir ${CMAKE_CURRENT_SOURCE_DIR} NAME)

    add_custom_command(
        OUTPUT ${dir}_checkstyle-report
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/filefilter.txt
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMAND ${PYTHON_EXECUTABLE}
        ARGS ${PROJECT_SOURCE_DIR}/thirdparty/nsiqcppstyle/nsiqcppstyle.py ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_custom_command(
        OUTPUT ${dir}_checkstyle-xml
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/filefilter.txt
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMAND ${PYTHON_EXECUTABLE}
        ARGS ${PROJECT_SOURCE_DIR}/thirdparty/nsiqcppstyle/nsiqcppstyle.py --output=xml ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/filefilter.txt
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy ${PROJECT_SOURCE_DIR}/contrib/filefilter.txt ${CMAKE_CURRENT_SOURCE_DIR}/
    )

    add_custom_target(
        checkstyle_${dir}
        DEPENDS ${dir}_checkstyle-report
    )

    add_custom_target(
        checkstylexml_${dir}
        DEPENDS ${dir}_checkstyle-xml
    )


    add_dependencies(checkstyle checkstyle_${dir})
    add_dependencies(checkstylexml checkstylexml_${dir})

  endif(PYTHONINTERP_FOUND)
endfunction()
