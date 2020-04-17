cmake_minimum_required(VERSION 2.4)

project(badway)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        badway
        src/main.cpp
        src/sha256.c
        src/mylib.cpp
#        include/main.h
#        include/mylib.h
#        include/nums.h
#        include/PI64.h
#        include/sha256.h
#        include/typos.h
#        openssl/configuration.h
#        openssl/core.h
#        openssl/core_numbers.h
#        openssl/crypto.h
#        openssl/cryptoerr.h
#        openssl/e_os2.h
#        openssl/ebcdic.h
#        openssl/macros.h
#        openssl/md32_common.h
#        openssl/opensslconf.h
#        openssl/opensslv.h
#        openssl/safestack.h
#        openssl/sha.h
#        openssl/stack.h
#        openssl/symhacks.h
#        openssl/types.h
)

include_directories(
        openssl
        include
        PI
)

add_compile_options(-Wno-nullability-completeness)
