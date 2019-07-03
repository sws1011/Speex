# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library( # Sets the name of the library.
        speex-lib

        # Sets the library as a shared library.
        SHARED

        ./libspeex/bits.c
        ./libspeex/buffer.c
        ./libspeex/cb_search.c
        ./libspeex/exc_10_16_table.c
        ./libspeex/exc_10_32_table.c
        ./libspeex/exc_20_32_table.c
        ./libspeex/exc_5_256_table.c
        ./libspeex/exc_5_64_table.c
        ./libspeex/exc_8_128_table.c
        ./libspeex/fftwrap.c.
        ./libspeex/filterbank.c
        ./libspeex/filters.c
        ./libspeex/gain_table.c
        ./libspeex/gain_table_lbr.c
        ./libspeex/hexc_10_32_table.c
        ./libspeex/hexc_table.c
        ./libspeex/high_lsp_tables.c
        ./libspeex/jitter.c
        ./libspeex/kiss_fft.c
        ./libspeex/kiss_fftr.c
        ./libspeex/lpc.c
        ./libspeex/lsp.c
        ./libspeex/lsp_tables_nb.c
        ./libspeex/ltp.c
        ./libspeex/mdf.c
        ./libspeex/modes.c
        ./libspeex/modes_wb.c
        ./libspeex/nb_celp.c
        ./libspeex/preprocess.c
        ./libspeex/quant_lsp.c
        ./libspeex/resample.c
        ./libspeex/sb_celp.c
        ./libspeex/scal.c
        ./libspeex/smallft.c
        ./libspeex/speex.c
        ./libspeex/speex_callbacks.c
        ./libspeex/speex_header.c
        ./libspeex/stereo.c
        ./libspeex/vbr.c
        ./libspeex/vq.c
        ./libspeex/window.c
        native-lib.cpp
        # Provides a relative path to your source file(s).
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        speex-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})