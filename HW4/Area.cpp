#include "Area.h"
using namespace mtm ;

/**
 * Area.cpp , all functions are explained in Area.h .
 */

Area::Area(const std::string& name): area_name(name), reachable_areas(),
                                     groups(){
    if (name.empty()){
        throw AreaInvalidArguments() ;
    }
}

void Area::addReachableArea(const std::string& area_name){
    reachable_areas.insert(area_name);
}

bool Area::isReachable(const std::string& area_name) const {
    if (this->area_name==area_name) {
        return true;
    }
    return reachable_areas.contains(area_name);
}

void Area::groupArrive(const string& group_name, const string& clan,
                         map<string, Clan>& clan_map) {
    map<string,Clan>::const_iterator c_it = clan_map.find(clan);
    if (c_it == clan_map.end()) {
        throw AreaClanNotFoundInMap() ;
    }
    if (!clan_map.at(clan).doesContain(group_name)){
        throw AreaGroupNotInClan();
    }
    if (findGroup(group_name)!=-1){
        throw AreaGroupAlreadyIn();
    }
}

void Area::groupLeave(const std::string& group_name) {
    int group_index = findGroup(group_name) ;
    if (group_index==-1) {
        throw AreaGroupNotFound();
    }
    groups.erase(groups.begin()+group_index);
}

MtmSet<std::string> Area::getGroupsNames() const {
    MtmSet<std::string> groups_names ;
    for (unsigned int i = 0; i < groups.size(); ++i) {
        if (!((*(groups[i])).getName().empty())) { //check if name is not ""
            groups_names.insert((*(groups[i])).getName());
        }
    }
    return groups_names;
}