#include "SpellcasterSrv.h"

SpellcasterSrv::SpellcasterSrv() {
    _lastScan = boost::posix_time::time_from_string("2000-01-01 00:00:00.00");
}

bool SpellcasterSrv::setup() {
	return true;
}

bool SpellcasterSrv::update() {
    int sec = secondsFromLastScan();
    if (sec >= 60) {
        _lastScan = boost::posix_time::microsec_clock::local_time();
        std::cout << "start update!" << std::endl;
        std::cout << SpellcasterUtils::httpsGetRequest("games.ravenblack.net", "/players?order=&showidle=1");
    }

	return true;
}

int SpellcasterSrv::secondsFromLastScan() {
    boost::posix_time::ptime current_date = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration td = current_date - _lastScan;

    
    std::cout << "last scan: " << _lastScan << " current time " << current_date << " diff in sec " << td.total_seconds() << std::endl;

    return td.total_seconds();
}