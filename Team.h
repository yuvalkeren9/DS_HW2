//
// Created by יובל קרן on 12/20/2022.
//

#ifndef DS2_TEAM_H
#define DS2_TEAM_H


class Node;

class Team {
private:
    int teamId;
    Node* teamRepresentative;
    long long int numbOfPlayersInTeam;
    long long int numOfGamesPlayed;

public:
    Team(int teamId) : teamId(teamId), teamRepresentative(nullptr), numbOfPlayersInTeam(0), numOfGamesPlayed(0) {};
    Node* getTeamRepresentative() const;
    void setTeamRepresentative(Node* team);
    long long int getNumOfPlayersInTeam() const;
    long long int getNumOfGamesPlayed() const;
    void setNumOfGamesPlayed(long long int toSet);


    void increaseNumberOfPlayers(int numOfPlayersAdded);


    bool operator==(const Team& other) const;
    bool operator>(const Team& other) const;
    bool operator<(const Team& other) const;
};


#endif //DS2_TEAM_H
