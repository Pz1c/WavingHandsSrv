#ifndef SPELLCASTERSRV_H
#define SPELLCASTERSRV_H

#include <boost/date_time/posix_time/posix_time.hpp>

#include "SpellcasterUtils.h"


class SpellcasterSrv
{
public:
    SpellcasterSrv();
    ~SpellcasterSrv();
    bool setup();
    bool update();

protected:
    int secondsFromLastScan();
    void updateWarlockList();

protected:
// utilities
    void parseWarlocks(std::string &data);

private:
    void loadData();
    void saveData();

private:
    boost::posix_time::ptime _lastScan;

    //std::map<std::string, >

};

#endif // SPELLCASTERSRV_H
