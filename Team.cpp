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
