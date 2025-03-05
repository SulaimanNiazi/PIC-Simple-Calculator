# The following variables contains the files used by the different stages of the build process.
set(PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)
set(PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_compile "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c")
set_source_files_properties(${PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(PIC_Simple_Calculator_default_default_XC8_FILE_TYPE_link)

# The (internal) path to the resulting build image.
set(PIC_Simple_Calculator_default_internal_image_name "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/PIC_Simple_Calculator/default/PIC_Calculator.hex")

# The name of the resulting image, including namespace for configuration.
set(PIC_Simple_Calculator_default_image_name "PIC_Simple_Calculator_default_PIC_Calculator.hex")

# The name of the image, excluding the namespace for configuration.
set(PIC_Simple_Calculator_default_original_image_name "PIC_Calculator.hex")

# The output directory of the final image.
set(PIC_Simple_Calculator_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/PIC_Simple_Calculator")
