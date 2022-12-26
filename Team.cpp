//
// Created by יובל קרן on 12/20/2022.
//

#include "Team.h"

Node *Team::getTeamRepresentative() const {
    return teamRepresentative;
}

void Team::setTeamRepresentative(Node* team) {
    teamRepresentative = team;

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

void Team::increaseNumberOfPlayers(int numOfPlayersAdded) {
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
