//
// Created by eladm on 27/12/2022.
//

#ifndef DS2_TEAMBYABILITY_H
#define DS2_TEAMBYABILITY_H

class teamByAbility {
private:
    int teamId;
    int teamAbility;

public:
    teamByAbility(int teamId):teamId(teamId),teamAbility(0){};
    int getTeamAbility();
    int getId();
    void IncTeamAbility(int toInc);

    bool operator==(const teamByAbility& other) const;
    bool operator>(const teamByAbility& other) const;
    bool operator<(const teamByAbility& other) const;

    //lines added by yuval
    void updateId(int id);

};

#endif //DS2_TEAMBYABILITY_H
