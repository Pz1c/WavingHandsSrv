#include "SpellcasterSrv.h"

SpellcasterSrv::SpellcasterSrv() {
    _lastScan = boost::posix_time::time_from_string("2000-01-01 00:00:00.00");
    loadData();
}

SpellcasterSrv::~SpellcasterSrv() {
    saveData();
}

bool SpellcasterSrv::setup() {
	return true;
}

bool SpellcasterSrv::update() {
    updateWarlockList();

	return true;
}

void SpellcasterSrv::updateWarlockList() {
    int sec = secondsFromLastScan();
    if (sec < 60) {
        return;
    }

    _lastScan = boost::posix_time::microsec_clock::local_time();
    std::cout << "start update!" << std::endl;
    std::string topList = SpellcasterUtils::httpsGetRequest("games.ravenblack.net", sec > 24 * 60 * 60 ? "/players?order=&showidle=1" : "/players?order=&showidle=0");
    parseWarlocks(topList);
}

void SpellcasterSrv::parseWarlocks(std::string& data) {
    int idx1 = data.find_first_of("<TD CLASS=darkbg>");
    // if (idx1 )
}

int SpellcasterSrv::secondsFromLastScan() {
    boost::posix_time::ptime current_date = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration td = current_date - _lastScan;

    
    std::cout << "last scan: " << _lastScan << " current time " << current_date << " diff in sec " << td.total_seconds() << std::endl;

    return td.total_seconds();
}

void SpellcasterSrv::loadData() {

}

void SpellcasterSrv::saveData() {

}