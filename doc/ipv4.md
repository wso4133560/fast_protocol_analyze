# ipv4 script description
pro IPV4 {
    version(Version)                                  : bit(0, 4);
    headerlen(Header Length)                          : bit(4, 4);
    diffService(Differentiated Services Codepoint)    : byte(1);
    len(Total Length)                                 : byte(2);
    iden(identification)                              : byte(2);
    
    flags(Flags)                                      : struct(2);
    rbit(reserved bit)                                : bit(0, 1) in flags;
    dFrag(Don't fragment)                             : bit(1, 1) in flags;
    mfrag(More fragments)                             : bit(2, 1) in flags;
    fOffset(Fragmet Offset)                           : bit(3, 13) in flags;

    tLive(Time to Live)                               : byte(1);
    proto(Protocal)                                   : byte(1);
    hchecksum(Header Checksum)                        : byte(2);
    src(Source Address)                               : byte(4);
    dst(Dst Address)                                  : byte(4);

    version -> decode -> gone;
    headerlen -> decode -> gone;
    diffService -> decode -> gone;
    len -> decode -> gone;
    iden -> decode -> gone;
    flags -> decode -> gone;
    rbit -> decode;
    dFrag -> decode;
    mfrag -> decode;
    fOffset -> decode;
    flags -> gone;
    tLive -> decode -> gone;
    proto -> decode -> gone;
    hchecksum -> decode -> gone;
    src -> decode -> gone;
    dst -> decode -> gone;

    if proto == 0x17:
        jump udp;
}
