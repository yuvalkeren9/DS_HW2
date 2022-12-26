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

int Team::getNumOfPlayersInTeam() const {
    return numbOfPlayersInTeam;
}
