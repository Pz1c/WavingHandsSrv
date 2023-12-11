#ifndef QGAMECONSTANT
#define QGAMECONSTANT

#include <vector>
#include <map>
#include <string>

static std::vector<std::string> _lstAI({"CONSTRUCT", "EARTHGOLEM", "IRONGOLEM", "BEZOAR", "ENNEAD", "ADYVIO", "XAERO", "WAORALACKS", "UWULEKAI","STIOCILIA","ICRAEVERRA","DAELAZAR"});
static std::map<std::string, int> MAP_COLOR_TO_SECONDS({{"#00FF00",1},{"#11EE00",120},{"#22DD00",300},{"#33CC00",600},{"#44BB00",1800},
                                               {"#55AA00",3600},{"#669900",7200},{"#778800",21600},{"#887700",43200},{"#996600",86400},
                                               {"#AA5500",130000},{"#BB4400",172800},{"#CC3300",259200},{"#DD2200",500000},
                                               {"#EE1100",1000000},{"#FF0000",20000000}});


#endif // QGAMECONSTANT

