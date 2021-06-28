project(clashdomedst)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( clashdomedst clashdomedst clashdomedst.cpp )
target_include_directories( clashdomedst PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( clashdomedst ${CMAKE_SOURCE_DIR}/../ricardian )