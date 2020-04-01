#include "World.h"

using namespace mtm ;
using  std::ostream ;
using std::endl;
/**
 * World.cpp , all functions are explained in World.h .
 */
World::World(): clan_map(),areas_map() {}

void World::addClan(const string& new_clan){
    if (new_clan.empty()){
        throw WorldInvalidArgument() ;
    }
    if (checkClanExiest(new_clan)){
        throw WorldClanNameIsTaken() ;
    }
    Clan clan(new_clan);
    clan_map.insert(std::pair<string,Clan>(new_clan,clan));
}

void World::addArea(const string& area_name, AreaType type){
    if (area_name.empty()){
        throw WorldInvalidArgument() ;
    }
    if (checkAreaExiest(area_name)){
        throw WorldAreaNameIsTaken() ;
    }
    switch (type) {
        case PLAIN : {
            AreaPtr new_plain(new Plain(area_name));
            areas_map.insert(std::pair<string, AreaPtr>(area_name, new_plain));
            break;
        }
        case MOUNTAIN : {
            AreaPtr new_mountain(new Mountain(area_name));
            areas_map.insert(
                    std::pair<string, AreaPtr>(area_name, new_mountain));
            break;
        }
        case RIVER  : {
            AreaPtr new_river (new River(area_name));
           areas_map.insert(std::pair<string,AreaPtr>(area_name,new_river));
            break ;
        }
    }
}

void World::addGroup(const string& group_name, const string& clan_name, int
num_children, int num_adults, const string& area_name) {
    if ((group_name.empty()) ||(num_children<0) || (num_adults<0) ||
            ((num_adults==0)&&(num_children==0))){
        throw WorldInvalidArgument() ;
    }
    if (checkIfGroupNameExiest(group_name)){
        throw WorldGroupNameIsTaken() ;
    }
    if (!checkClanExiest(clan_name)){
        throw WorldClanNotFound() ;
    }
    if (!checkAreaExiest(area_name)){
        throw WorldAreaNotFound() ;
    }
    //adding the group to the clan map , then adding it to the area.
    clan_map.at(clan_name).addGroup(Group(group_name,num_children,num_adults));
    (*(areas_map.at(area_name))).groupArrive(group_name,clan_name,clan_map) ;
}

void World::makeReachable(const string& from, const string& to){
    if ((!checkAreaExiest(from))|| (!checkAreaExiest(to)) ){
        throw WorldAreaNotFound() ;
    }
    (*areas_map.at(from)).addReachableArea(to);
}

void World::moveGroup(const string& group_name, const string& destination){
    if (!checkIfGroupNameExiest(group_name)){
        throw WorldGroupNotFound() ;
    }
    if ((!checkAreaExiest(destination))){
        throw WorldAreaNotFound() ;
    }
    if((*(areas_map.at(destination))).getGroupsNames().contains(group_name)) {
        throw WorldGroupAlreadyInArea();
    }
    string area_name = findAreaThatHasGroup(group_name);
    if (!((*(areas_map.at(area_name))).isReachable(destination))){
        throw WorldAreaNotReachable();
    }
    string clan_name = findClanThatHasGroup(group_name);
    //remove the group from the source area , than add it to the destination.
    (*(areas_map.at(area_name))).groupLeave(group_name);
    (*(areas_map.at(destination))).groupArrive(group_name,clan_name,clan_map);
}

void World::makeFriends(const string& clan1, const string& clan2) {
    if ((!checkClanExiest(clan1))||(!checkClanExiest(clan2))){
        throw WorldClanNotFound() ;
    }
    clan_map.at(clan1).makeFriend(clan_map.at(clan2));
}

void World::uniteClans(const string& clan1, const string& clan2, const
string& new_name) {
    if (new_name.empty()){
        throw WorldInvalidArgument() ;
    }
    if (checkClanExiest(new_name)){
        throw WorldClanNameIsTaken() ;
    }
    if ((!checkClanExiest(clan1))||(!checkClanExiest(clan2))){
        throw WorldClanNotFound() ;
    }
    clan_map.at(clan1).unite(clan_map.at(clan2),new_name) ;
    Clan temp_clan = clan_map.at(clan1) ;
    clan_map.erase(clan1);
    clan_map.erase(clan2);
    clan_map.insert(std::pair<string,Clan>(new_name,temp_clan));
    makeFriendsUnitedClan(clan_map.at(new_name)) ;
}

void World::printGroup(std::ostream& os, const string& group_name) const {
    if (!checkIfGroupNameExiest(group_name)){
        throw WorldGroupNotFound() ;
    }
    os <<*(clan_map.at(findClanThatHasGroup(group_name)).getGroup(group_name));
    os <<"Group's current area: "<< findAreaThatHasGroup(group_name) << endl ;
}

void World::printClan(std::ostream& os, const string& clan_name) const {
    if (!checkClanExiest(clan_name)) {
        throw WorldClanNotFound() ;
    }
    os << clan_map.at(clan_name) ;
}



