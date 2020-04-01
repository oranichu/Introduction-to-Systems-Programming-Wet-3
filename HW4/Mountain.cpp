#include "Mountain.h"
using namespace mtm ;
/**
 * Mountain.cpp , all functions are explained in Mountain.h .
 */
Mountain::Mountain(const std::string& name) : Area(name),
                                              ruler(nullptr) {}

void Mountain::groupArrive(const string& group_name, const string& clan,
                           map<string, Clan>& clan_map) {
    Area::groupArrive(group_name,clan,clan_map);
    GroupPointer arrived_group = clan_map.at(clan).getGroup(group_name) ;
    if (ruler == nullptr) {
        ruler=arrived_group;
        groups.insert(groups.begin(),arrived_group);
        return ;
    }
    if ((*ruler).getClan()==clan) {
        if ((*arrived_group)>(*ruler)) {
            ruler=arrived_group ;
        }
        groups.insert(groups.begin(),arrived_group);
        return ;
    }
    if ((*arrived_group).fight(*ruler)==WON){
        ruler=arrived_group ;
        groups.insert(groups.begin(),arrived_group);
        deleteEmptyGroups();
        return ;
    }
    if ((*arrived_group).getSize()!=0){
        groups.insert(groups.begin(),arrived_group);//
    }//if they lost we don't want to add an empty group to the vector.
}

void Mountain::groupLeave(const std::string& group_name){
    int group_index = findGroup(group_name);
    if (group_index==-1) {
        throw AreaGroupNotFound();
    }
    groups.erase(groups.begin()+group_index);
    if((*ruler).getName()!=group_name) {
        return ;
    }
    GroupPointer strongest = findStrongestGroup
            ((*groups[group_index]).getClan());
    ruler= strongest;
}