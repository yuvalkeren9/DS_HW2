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

public:
    Team(int teamId) : teamId(teamId), teamRepresentative(nullptr){};
    Node* getTeamRepresentative() const;
    void setTeamRepresentative(Node* team);
};


#endif //DS2_TEAM_H
