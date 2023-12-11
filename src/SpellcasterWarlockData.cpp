#include "SpellcasterWarlockData.h"

#define qDebug() std::count

SpellcasterWarlockData::SpellcasterWarlockData() {

}

SpellcasterWarlockData::SpellcasterWarlockData(std::string Name, bool Registered, int Ladder, int Melee, int Played, int Won, int Died, int Elo, std::string Color, boost::posix_time::ptime LastActivity, bool Mobile)
{
    init(Name, Registered, Ladder, Melee, Played, Won, Died, Elo, Color, LastActivity, Mobile);
}

SpellcasterWarlockData::SpellcasterWarlockData(std::string &Raw, bool FromIni) {
    if (FromIni) {
        parseIniAndInit(Raw);
    }
    else if (Raw.find_first_of("END_ROW") != -1) {
        parseSiteAndInit(Raw);
    }
    else {
        parseAndInit(Raw);
    }
}

void SpellcasterWarlockData::init(std::string Name, bool Registered, int Ladder, int Melee, int Played, int Won, int Died, int Elo, std::string Color, boost::posix_time::ptime LastActivity, bool Mobile, int warlockId)
{
    _name = Name;
    _registered = Registered;
    _ladder = Ladder;
    _melee = Melee;
    _played = Played;
    _won = Won;
    _died = Died;
    _elo = Elo;
    _color = Color;
    if (LastActivity != boost::posix_time::not_a_date_time) {
        _lastActivity = LastActivity;
    }
    else {
        _lastActivity = boost::posix_time::not_a_date_time;
    }
    _ai = SpellcasterUtils::isAI(_name);
    _mobile = Mobile;
    _warlockId = warlockId;
}

void SpellcasterWarlockData::parseSiteAndInit(std::string Raw) {
    std::vector<std::string> data;
    boost::split(data, Raw, boost::is_any_of(","));
    bool Registered = data.at(0).compare("1") == 0;
    std::string Name = data.at(1);
    int Ladder = std::stoi(data.at(2));
    int Melee = std::stoi(data.at(3));
    int Played = std::stoi(data.at(4));
    int Won = std::stoi(data.at(5));
    int Died = std::stoi(data.at(6));
    int Elo = std::stoi(data.at(7));
    std::string Color = data.at(8);
    bool Mobile = std::stoi(data.at(10)) == 1;
    boost::posix_time::ptime la = boost::posix_time::microsec_clock::local_time() - boost::posix_time::seconds(std::stoi(data.at(11)));

    init(Name, Registered, Ladder, Melee, Played, Won, Died, Elo, Color, la, Mobile);
}


//std::string SpellcasterWarlockData::toString() const {
//    return std::string("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11")
//        .arg(boolToIntS(_registered), _name, intToStr(_ladder), intToStr(_melee) // 1-4
//             ,intToStr(_played), intToStr(_won), intToStr(_died), intToStr(_elo)) //5-8
//        .arg(_color, intToStr(_lastActivity), boolToIntS(_mobile)); // 9-11


void SpellcasterWarlockData::parseIniAndInit(std::string Raw) {
    std::vector<std::string> data;
    boost::split(data, Raw, boost::is_any_of(","));
    bool Registered = data.at(0).compare("1") == 0;
    std::string Name = data.at(1);
    int Ladder = data.at(2).toInt();
    int Melee = data.at(3).toInt();
    int Played = data.at(4).toInt();
    int Won = data.at(5).toInt();
    int Died = data.at(6).toInt();
    int Elo = data.at(7).toInt();
    std::string Color = data.at(8);
    boost::posix_time::ptime la = data.at(9).toInt();
    bool Mobile = data.at(10).toInt() == 1;
    int id = data.at(11).toInt();
    //qDebug() << "SpellcasterWarlockData::parseIniAndInit" << Raw << Registered << Name << Ladder << Melee << Played << Won << Died << Elo << la << id;

    init(Name, Registered, Ladder, Melee, Played, Won, Died, Elo, Color, la, Mobile, id);
}

void SpellcasterWarlockData::parseAndInit(std::string Raw) {
    int pos = 0;
    std::string Registered = SpellcasterUtils::getStringFromData(Raw, "/img/reg.png", "ALT=\"", "!", pos, true);
    std::string Name = SpellcasterUtils::getStringFromData(Raw, "<A HREF=", "/player/", ".html", pos);
    int Ladder = SpellcasterUtils::getIntFromPlayerData(Raw, "<TD ALIGN", ">", "<", pos);
    int Melee = SpellcasterUtils::getIntFromPlayerData(Raw, "<TD ALIGN", ">", "<", pos);
    int Played = SpellcasterUtils::getIntFromPlayerData(Raw, "<TD ALIGN", ">", "<", pos);
    int Won = SpellcasterUtils::getIntFromPlayerData(Raw, "<TD ALIGN", ">", "<", pos);
    int Died = SpellcasterUtils::getIntFromPlayerData(Raw, "<TD ALIGN", ">", "<", pos);
    int Elo = SpellcasterUtils::getIntFromPlayerData(Raw, "<TD ALIGN", ">", "<", pos);
    std::string Color = SpellcasterUtils::getStringFromData(Raw, "<TD STYLE=", "background-color:", ";", pos);
    boost::posix_time::ptime la = getLastActivityByColor(Color);
    //qDebug() << "SpellcasterWarlockData::parseAndInit" << Raw << Registered << Name << Ladder << Melee << Played << Won << Died << Elo << Active << Color;

    init(Name, !Registered.empty(), Ladder, Melee, Played, Won, Died, Elo, Color, la, false);
}

boost::posix_time::ptime SpellcasterWarlockData::getLastActivityByColor(const std::string Color) {
    boost::posix_time::ptime curr_time = boost::posix_time::microsec_clock::local_time();
    int dec_sec;
    if (MAP_COLOR_TO_SECONDS.find(Color) != MAP_COLOR_TO_SECONDS.end()) {
        dec_sec = MAP_COLOR_TO_SECONDS[Color];
    }
    else {
        dec_sec = 20000100;
    }
    //qDebug() << "SpellcasterWarlockData::getLastActivityByColor" << _name << Color << curr_time << dec_sec << curr_time - dec_sec;
    // boost::posix_time::time_duration dec(boost::posix_time::seconds(dec_sec));
    return curr_time - boost::posix_time::seconds(dec_sec);
}

void SpellcasterWarlockData::setMobile(bool newMobile)
{
    _mobile = newMobile;
}

void SpellcasterWarlockData::setLastActivity(boost::posix_time::ptime newLastActivity)
{
    _lastActivity = newLastActivity;
}

void SpellcasterWarlockData::setElo(int newElo)
{
    _elo = newElo;
}

void SpellcasterWarlockData::setDied(int newDied)
{
    _died = newDied;
}

void SpellcasterWarlockData::setWon(int newWon)
{
    _won = newWon;
}

void SpellcasterWarlockData::setPlayed(int newPlayed)
{
    _played = newPlayed;
}

void SpellcasterWarlockData::setMelee(int newMelee)
{
    _melee = newMelee;
}

void SpellcasterWarlockData::setLadder(int newLadder)
{
    _ladder = newLadder;
}

void SpellcasterWarlockData::setRegistered(bool newRegistered)
{
    _registered = newRegistered;
}

int SpellcasterWarlockData::warlockId() const
{
    return _warlockId;
}

void SpellcasterWarlockData::setWarlockId(int newWarlockId)
{
    _warlockId = newWarlockId;
}

bool SpellcasterWarlockData::mobile() const
{
    return _mobile;
}

bool SpellcasterWarlockData::ai() const
{
    return _ai;
}

boost::posix_time::ptime SpellcasterWarlockData::lastActivity() const
{
    return _lastActivity;
}

std::string SpellcasterWarlockData::toString() const {
    return std::string("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12")
        .arg(boolToIntS(_registered), _name, intToStr(_ladder), intToStr(_melee) // 1-4
            , intToStr(_played), intToStr(_won), intToStr(_died), intToStr(_elo)) //5-8
        .arg(_color, intToStr(_lastActivity), boolToIntS(_mobile), intToStr(_warlockId)); // 9-12
}

//std::string SpellcasterWarlockData::toJSON() const {
//    boost::posix_time::ptime curr_time = QDateTime::currentSecsSinceEpoch();
//    std::string active = boolToIntS(curr_time - _lastActivity <= 300);
//    return std::string("{\"r\":%1,\"n\":\"%2\",\"l\":%3,\"m\":%4,\"p\":%5,\"w\":%6,\"d\":%7,\"e\":%8,\"c\":\"%9\","
//        "\"la\":%10,\"mob\":%11,\"a\":%12,\"id\":%13}")
//        .arg(boolToIntS(_registered), _name, intToStr(_ladder), intToStr(_melee) // 1-4
//            , intToStr(_played), intToStr(_won), intToStr(_died), intToStr(_elo)) //5-8
//        .arg(_color, intToStr(_lastActivity), boolToIntS(_mobile), active, intToStr(_warlockId)); // 9-15
//}


bool SpellcasterWarlockData::online() const {
    return _ai || (QDateTime::currentSecsSinceEpoch() - _lastActivity <= 5 * 60);
}

int SpellcasterWarlockData::elo() const
{
    return _elo;
}

int SpellcasterWarlockData::died() const
{
    return _died;
}

int SpellcasterWarlockData::won() const
{
    return _won;
}

int SpellcasterWarlockData::played() const
{
    return _played;
}

int SpellcasterWarlockData::melee() const
{
    return _melee;
}

int SpellcasterWarlockData::ladder() const
{
    return _ladder;
}

bool SpellcasterWarlockData::registered() const
{
    return _registered;
}

const std::string& SpellcasterWarlockData::name() const
{
    return _name;
}