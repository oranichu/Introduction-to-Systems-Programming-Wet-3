#include "Plain.h"
using namespace mtm ;

/**
 * Plain.cpp , all functions are explained in Plain.h .
 */
Plain::Plain(const std::string& name) : Area(name) {}

void Plain::groupArrive(const string& group_name, const string& clan,
                 map<string, Clan>& clan_map) {
    Area::groupArrive(group_name,clan,clan_map);
    int third_of_clan = ceil((clan_map.at(clan).getSize())/3);
    GroupPointer group_ptr = clan_map.at(clan).getGroup(group_name);
    if ((*group_ptr).getSize()<third_of_clan){
        uniteGroups(clan,third_of_clan,group_ptr);
        return ;
    }
    if ((*group_ptr).getSize()<MIN_SIZE_FOR_SPLIT) {
        groups.insert(groups.begin(),group_ptr);
        return ;
    }
    divideGroups(clan,clan_map,group_ptr);
}