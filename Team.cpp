//
// Created by יובל קרן on 12/20/2022.
//

#include "Team.h"

Node *Team::getTeamRepresentative() const {
    return teamRepresentative;
}

void Team::setTeamRepresentative(Node* player) {
    teamRepresentative = player;

}

bool Team::operator>(const Team &other) const {
    if(teamId > other.teamId){
        return true;
    }
    else{
        return false;
    }
}

bool Team::operator==(const Team &other) const {
    if (teamId == other.teamId){
        return true;
    }
    else{
        return false;
    }
}

void Team::increaseNumberOfPlayers(long long int numOfPlayersAdded) {
    numbOfPlayersInTeam += numOfPlayersAdded;

}

long long int Team::getNumOfPlayersInTeam() const {
    return numbOfPlayersInTeam;
}

bool Team::operator<(const Team &other) const {
    return teamId < other.teamId;
}

int Team::getNumOfGamesPlayed() const {
    return numOfGamesPlayed;
}

void Team::incNumOfGamesPlayed(int toSet) {
    numOfGamesPlayed += toSet;
}

bool Team::getIsActive() const {
    return isActive;
}

void Team::setIsActive(bool condition) {
    isActive = condition;
}

bool Team::getIsQualified() const {
    return isQualified;
}

void Team::setIsQualified(bool condition) {
    isQualified = condition;
}

void Team::increaseTeamAbility(int ability) {
    teamAbility += ability;
}

int Team::getTeamAbility() const {
    return teamAbility;
}

void Team::increasePoints(int pointsToAdd) {
    points += pointsToAdd;
}

int Team::getPoints() const {
    return points;
}

void Team::updateTeamSpiritRightSide(permutation_t permut) {
    teamSpirit = teamSpirit * permut;
}

void Team::updateTeamSpiritLeftSide(permutation_t permut) {
    teamSpirit = permut * teamSpirit;
}

permutation_t Team::getTeamTotalSpirit() const {
    return teamSpirit;
}

int Team::getTeamTotalScore() const {
    return points + teamAbility;
}

teamByAbility *Team::getTeamByAbility() const {
    return teamByAbilityPtr;
}

void Team::setTeamByAbilityPtr(teamByAbility *toSet) {
    this->teamByAbilityPtr=toSet;
}

void Team::copyTeamStats(Team* other) {

    teamSpirit=other->teamSpirit;
//    teamAbility=other->teamAbility;


//    teamByAbilityPtr=other->teamByAbilityPtr;

    teamRepresentative=other->teamRepresentative;
    numOfGamesPlayed=other->numOfGamesPlayed;
    numbOfPlayersInTeam=other->numbOfPlayersInTeam;
    isActive=other->isActive;
    isQualified=other->isQualified;
    points=other->points;
}

int Team::getTeamId() {
    return teamId;
}
