//
// Created by eladm on 27/12/2022.
//

#include "teamByAbility.h"


int teamByAbility::getTeamAbility() {
    return teamAbility;
}

void teamByAbility::IncTeamAbility(int toInc) {
    this->teamAbility+=toInc;
}

bool teamByAbility::operator>(const teamByAbility &other) const {
    if(teamAbility == other.teamAbility)
    {
        if(teamId>other.teamId)
            return true;
        return false;
    }
    if(teamAbility > other.teamAbility){
        return true;
    }
        return false;
}
bool teamByAbility::operator==(const teamByAbility &other) const {
    if (teamAbility == other.teamAbility){
        return true;
    }
    else{
        return false;
    }
}
bool teamByAbility::operator<(const teamByAbility &other) const {
    return teamAbility < other.teamAbility;
}

int teamByAbility::getId() {
    return teamId;
}
