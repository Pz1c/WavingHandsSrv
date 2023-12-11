#ifndef SPELLCASTERWARLOCKDATA_H
#define SPELLCASTERWARLOCKDATA_H

#include <list>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "SpellcasterUtils.h"

class SpellcasterWarlockData
{
public:
    SpellcasterWarlockData();
    SpellcasterWarlockData(std::string Name, bool Registered, int Ladder, int Melee, int Played, int Won, int Died, int Elo,
        std::string Color, boost::posix_time::ptime LastActivity, bool Mobile);
    SpellcasterWarlockData(std::string &Raw, bool FromIni = false);

    std::string toString() const;
    //std::string toJSON() const;

    const std::string& name() const;

    bool registered() const;

    int ladder() const;

    int melee() const;

    int played() const;

    int won() const;

    int died() const;

    int elo() const;

    bool online() const;

    boost::posix_time::ptime lastActivity() const;

    bool ai() const;

    bool mobile() const;

    int warlockId() const;
    void setWarlockId(int newWarlockId);

    void setRegistered(bool newRegistered);

    void setLadder(int newLadder);

    void setMelee(int newMelee);

    void setPlayed(int newPlayed);

    void setWon(int newWon);

    void setDied(int newDied);

    void setElo(int newElo);

    void setLastActivity(boost::posix_time::ptime newLastActivity);

    void setMobile(bool newMobile);

protected:
    void parseAndInit(std::string Raw);
    void parseIniAndInit(std::string Raw);
    void parseSiteAndInit(std::string Raw);
    void init(std::string Name, bool Registered, int Ladder, int Melee, int Played, int Won, int Died, int Elo, std::string Color, boost::posix_time::ptime LastActivity, bool Mobile, int warlockId = 0);
    boost::posix_time::ptime getLastActivityByColor(const std::string Color);

private:
    std::string _name;
    bool _registered;
    bool _ai;
    int _ladder;
    int _melee;
    int _played;
    int _won;
    int _died;
    int _elo;
    int _warlockId;
    boost::posix_time::ptime _lastActivity;
    std::string _color;
    bool _mobile;

};

#endif // SPELLCASTERSRV_H
