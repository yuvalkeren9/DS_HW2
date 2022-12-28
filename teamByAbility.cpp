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
    if(teamAbility > other.teamAbility){
        return true;
    }
    else if (teamAbility < other.teamAbility){
        return false;
    }
    else{  //abilities are equal
        return (teamId > other.teamId) ;
    }
}

bool teamByAbility::operator==(const teamByAbility &other) const {
    if (teamId == other.teamId){
        return true;
    }
    else{
        return false;
    }
}

bool teamByAbility::operator<(const teamByAbility &other) const {
    if(teamAbility < other.teamAbility){
        return true;
    }
    else if (teamAbility > other.teamAbility){
        return false;
    }
    else{  //abilities are equal
        return (teamId < other.teamId) ;
    }
}


int teamByAbility::getId() {
    return teamId;
}
