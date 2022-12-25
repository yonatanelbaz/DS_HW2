#ifndef WORLDCUP
#define WORLDCUP
#include "worldcup23a2.h"
#define WIN 3
#define PLAYERS 11
#define TIE 1
#define RETURNTIE 0
#define TEAM1WINBYABILITY 1
#define TEAM2WINBYABILITY 3
#define TEAM1WINBYSPIRIT 2
#define TEAM2WINBYSPIRIT 4
using namespace std;

////TODO: Allocation errors
world_cup_t::world_cup_t()
{
    //this->teamsTree(Team::compare_TeamID);
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId<=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        std::shared_ptr<Team> newTeam(new Team(teamId, 0));

        if (this->teamsTree.findVal(newTeam) != nullptr) {
            return StatusType::FAILURE;
        }

        StatusType ret_status = this->teamsTree.insert(newTeam);
        return ret_status;
    }
    catch(const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{


    //removes it ONLYYY in the avl tree
    //TODO::remove it from the union find
    bool removed;
    if(teamId<=0) {
        return StatusType::INVALID_INPUT;
    }
    try{
        std::shared_ptr<Team> tempTeam =  std::shared_ptr<Team>(new Team(teamId, 0));
        auto tempTeamNode = this -> teamsTree.findVal(tempTeam);
        if(tempTeamNode == nullptr) {
            return StatusType::FAILURE;
        }
        //if(!tempTeamNode -> getValue() -> getPlayersById() -> IsEmpty()) {
        removed = teamsTree.remove(tempTeamNode -> getValue());


        if(removed) {
            return StatusType::SUCCESS;
        }

    }
    catch(const std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId<=0 || teamId<=0 || gamesPlayed<0 || cards<0 || spirit.isvalid()==false) {
        return StatusType::INVALID_INPUT;
    }
    try {
        std::shared_ptr<Player> newPlayer = std::make_shared<Player>(playerId, gamesPlayed, ability, cards, goalKeeper, spirit);
        if(this->worldCup.getPlayer(playerId)!= nullptr) {
            return StatusType::FAILURE;
        }
        std::shared_ptr<Team> newTeam = std::make_shared<Team>(teamId, 0);
        auto newTeamNode = this->teamsTree.findVal(newTeam);
        if (newTeamNode == nullptr) {
            return StatusType::FAILURE;
        }
        newTeam = newTeamNode->getValue();
        this->worldCup.addPlayer(newPlayer, newTeam);
        newTeam->incNumPlayers();
        newTeam->addSumAbility(ability);
        newPlayer-> setGamesPlayed(gamesPlayed - newTeam -> getGamesPlayed());

        if (newPlayer -> getGoalKeeper()) {
            newTeam->incGoalKeepers();
        }
        newTeam->setTeamSpirit(newTeam->getTeamSpirit() * spirit);
        // TODO: Your code goes here
        return StatusType::SUCCESS;
    }
    catch(const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Team> tempTeam1 =  std::shared_ptr<Team>(new Team(teamId1, 0));
    auto tempTeamNode1 = this -> teamsTree.findVal(tempTeam1);
    if(tempTeamNode1 == nullptr) {
        return StatusType::FAILURE;
    }
    std::shared_ptr<Team> tempTeam2 =  std::shared_ptr<Team>(new Team(teamId2, 0));
    auto tempTeamNode2 = this -> teamsTree.findVal(tempTeam2);
    if(tempTeamNode2 == nullptr) {
        return StatusType::FAILURE;
    }
    tempTeam1 = tempTeamNode1->getValue();
    tempTeam2 = tempTeamNode2->getValue();
    if(tempTeam1->getGoalkeepers()<=0 || tempTeam2->getGoalkeepers()<=0) {
        return StatusType::FAILURE;
    }
    int teamAbility1 = tempTeam1->getSumAbility() + tempTeam1->getPoints();
    int teamAbility2 = tempTeam2->getSumAbility() + tempTeam2->getPoints();
    tempTeam1->setGamesPlayed(tempTeam1->getGamesPlayed()+1);
    tempTeam2->setGamesPlayed(tempTeam2->getGamesPlayed()+1);
    if(teamAbility1>teamAbility2) {
        tempTeam1->setNumPoints(tempTeam1->getPoints() + WIN);
        return TEAM1WINBYABILITY;
        return StatusType::SUCCESS;
    }
    if(teamAbility2>teamAbility1) {
        tempTeam2->setNumPoints(tempTeam2->getPoints() + WIN);
        return TEAM1WINBYABILITY;
        return StatusType::SUCCESS;
    }
    ////TODO: calc team spirits
    int calcTeamSpirit1;
    int calcTeamSpirit2;
    if(calcTeamSpirit1>calcTeamSpirit2) {
        tempTeam1->setNumPoints(tempTeam1->getPoints() + WIN);
        return TEAM1WINBYSPIRIT;
        return StatusType::SUCCESS;
    }
    if(calcTeamSpirit2 > calcTeamSpirit1) {
        tempTeam2->setNumPoints(tempTeam2->getPoints() + WIN);
        return TEAM2WINBYSPIRIT;
        return StatusType::SUCCESS;
    }
    tempTeam1->setNumPoints(tempTeam1->getPoints() + TIE);
    tempTeam2->setNumPoints(tempTeam2->getPoints() + TIE);
    return RETURNTIE;

	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    try {
        if(playerId<=0) {
            return StatusType::INVALID_INPUT;
        }
        auto tempTeam = this->worldCup.findTeam(playerId);
        if(tempTeam == nullptr) {
            return StatusType::FAILURE;
        }
        if(tempTeam->getKnockedOut()==true) {
            return StatusType::FAILURE;
        }
        auto tempPlayerNode = this->worldCup.getPlayer(playerId);
        if(tempPlayerNode == nullptr) {
            return StatusType::FAILURE;
        }
        return tempTeam->getGamesPlayed()+tempPlayerNode->getValue()->getGamesPlayed();
    }
    catch(const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId<=0 || cards<0) {
        return StatusType::INVALID_INPUT;
    }
    auto tempPlayer = this->worldCup.getPlayer(playerId);
    if(tempPlayer == nullptr) {
        return StatusType::FAILURE;
    }
    auto tempTeam = this->worldCup.findTeam(playerId);
    if(tempTeam->getKnockedOut()==true) {
        return StatusType::FAILURE;
    }
    tempPlayer->addCards(cards);
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId<=0) {
        return StatusType::INVALID_INPUT;
    }
    auto tempPlayer = worldCup.getPlayer(playerId);
    if(tempPlayer == nullptr) {
        return StatusType::FAILURE;
    }
    return tempPlayer->getCards();
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try{
        shared_ptr<Team> tempTeam = shared_ptr<Team>(new Team(teamId, 0));
        auto tempTeamNode = this -> teamsTree.findVal(tempTeam);
        if(tempTeamNode == nullptr) {
            return StatusType::FAILURE;
        }
        return tempTeamNode -> getValue() -> getPoints();
    }
    catch(const std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }

    // TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(i>=this->numberOfTeams || i<0 || this->numberOfTeams==0) {
        return StatusType::FAILURE;
    }

    try{
        auto tempTeamNode = this -> teamsTree.findValWithRank(i);
        if(tempTeamNode == nullptr) {
            return StatusType::FAILURE;
        }
        return tempTeamNode -> getValue() -> getTeamId();
    }
    catch(const std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId<=0) {
        return StatusType::INVALID_INPUT;
    }
    auto tempPlayerNode = this->worldCup.getPlayer(playerId);
    if(tempPlayerNode == nullptr) {
        return StatusType::FAILURE;
    }
    auto tempTeam = this->worldCup.findTeam(playerId);
    if(tempTeam == nullptr) {
        return StatusType::FAILURE;
    }
    if(tempTeam->getKnockedOut() == true) {
        return StatusType::FAILURE;
    }
    
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
