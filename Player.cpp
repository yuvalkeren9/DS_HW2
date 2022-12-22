//
// Created by יובל קרן on 12/20/2022.
//

#include "Player.h"

int Player::getPlayerId() const {
    return playerId;
}

permutation_t Player::getSpirit() const {
    return spirit;
}

Team *Player::getTeam() const {
    return team;
}

void Player::setTeam(Team *teamToSet) {
    team = teamToSet;
}
