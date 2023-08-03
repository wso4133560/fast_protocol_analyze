project(analyze-pcap-tool)

add_executable(analyze-pcap-tool main.cpp)

target_link_libraries(analyze-pcap-tool pcap)
