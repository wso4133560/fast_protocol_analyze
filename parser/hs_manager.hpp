#include "template.h"
#include <hyperscan/hs.h>
#include <vector>


struct HsMatchInfo
{
    unsigned int id;
    uint16_t len;
};

static int HsMatchCount(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void *context)
{
    if (from)
    {
        // end match
        return 1;
    }

    HsMatchInfo& matchInfo = *(HsMatchInfo*)context;
    matchInfo.len = (uint16_t)to;
    matchInfo.id = id;
    return 0;
}

class HsManager : public Singleton<HsManager>
{
public:

private:
    hs_database_t*					m_database = nullptr;

};
