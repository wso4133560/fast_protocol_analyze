#include <stdio.h>
#include <pcap.h>

void packet_handler(u_char *user_data, struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    // 在这里进行数据包分析
    printf("Packet capture length: %d\n", pkthdr->caplen);
    printf("Packet total length: %d\n", pkthdr->len);
}

int main()
{
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr* header;
    const u_char *packet;
    const char *file_name = "/mnt/d/code/self-company/ipv4frags.pcap"; // 替换为你的pcap文件路径

    // 打开pcap文件
    handle = pcap_open_offline(file_name, errbuf);
    if (handle == NULL) {
        printf("Could not open pcap file %s: %s\n", file_name, errbuf);
        return 1;
    }

    // 循环读取pcap文件中的数据包
    while (1) {
        int ret = pcap_next_ex(handle, &header, &packet);
        if (ret == 1) {
            // 处理数据包
            packet_handler(NULL, header, packet);
        }
        else
        {
            break;
        }
    }

    // 关闭pcap文件
    pcap_close(handle);

    return 0;
}