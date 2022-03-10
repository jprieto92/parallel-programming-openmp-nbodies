# App: nbodyfile
add_executable(nbodyfile nbodyfile.cpp)
target_link_libraries(nbodyfile nbodyopt nbodybase nbodysoa nbodyaos)

# App: nbodyrnd
add_executable(nbodyrnd nbodyrnd.cpp)
target_link_libraries(nbodyrnd nbodyopt nbodybase nbodysoa nbodyaos)

