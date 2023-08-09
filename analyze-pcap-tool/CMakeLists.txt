project(analyze-pcap-tool)

add_executable(analyze-pcap-tool 
               ../parser/lex.c
               ../parser/parser.c
               main.cpp 
               ../parser/protocol.cpp)


target_link_libraries(analyze-pcap-tool pcap fl)
