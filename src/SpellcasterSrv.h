#ifndef SPELLCASTERSRV_H
#define SPELLCASTERSRV_H

#include <boost/date_time/posix_time/posix_time.hpp>

#include "SpellcasterUtils.h"

class SpellcasterSrv
{
public:
    SpellcasterSrv();
    bool setup();
    bool update();

protected:
    int secondsFromLastScan();

private:
    boost::posix_time::ptime _lastScan;

};

#endif // SPELLCASTERSRV_H
