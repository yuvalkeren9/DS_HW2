//
// Created by יובל קרן on 12/20/2022.
//

#ifndef DS2_TEAM_H
#define DS2_TEAM_H

#include "wet2util.h"
#include "teamByAbility.h"

class Node;

class Team {
private:
    int teamId;
    Node* teamRepresentative;
    long long int numbOfPlayersInTeam;
    long long int numOfGamesPlayed;
    bool isActive;
    bool isQualified;
    int points;
    int teamAbility;
    permutation_t teamSpirit;
    teamByAbility* teamByAbilityPtr;




public:
    Team(int teamId) : teamId(teamId), teamRepresentative(nullptr), numbOfPlayersInTeam(0), numOfGamesPlayed(0), isActive(true),
    isQualified(false), points(0), teamAbility(0), teamSpirit() {teamSpirit = permutation_t::neutral();};

    Node* getTeamRepresentative() const;
    void setTeamRepresentative(Node* player);
    long long int getNumOfPlayersInTeam() const;
    int getNumOfGamesPlayed() const;
    void incNumOfGamesPlayed(int toSet);


    void increaseNumberOfPlayers(long long int numOfPlayersAdded);

    bool getIsActive() const;
    void setIsActive(bool condition);

    bool getIsQualified() const;
    void setIsQualified(bool condition);

    int getTeamAbility() const;
    void increaseTeamAbility(int ability);

    void increasePoints(int pointsToAdd);
    int getPoints() const;
    void setTeamByAbilityPtr(teamByAbility* toSet);
    void copyTeamStats(Team* other);
    int getTeamId(); // for printing

    permutation_t getTeamTotalSpirit() const;
    teamByAbility* getTeamByAbility() const;

    /**
     *
     * @param permutaion to multiple to be on right side
     */
    void updateTeamSpiritRightSide(permutation_t permut);
    /**
     *
     * @param permutaion to multiple to be on left side
     */
    void updateTeamSpiritLeftSide(permutation_t permut);


    int getTeamTotalScore() const;


    bool operator==(const Team& other) const;
    bool operator>(const Team& other) const;
    bool operator<(const Team& other) const;
};


#endif //DS2_TEAM_H
