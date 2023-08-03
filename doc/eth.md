# ethernet script description
pro ETH {
    dst(Destination)    : byte(6);
    src(Source)         : byte(6);
    type(Type)          : byte(2);

    dst  -> decode -> gone;
    src  -> decode -> gone;
    type -> decode -> gone;

    if type == 0x0800:
        jump ipv4;
}

此处定义了gone关键字，gone关键字会消耗并移动解码的buffer