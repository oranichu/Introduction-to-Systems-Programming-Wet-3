#include "River.h"
using namespace mtm ;
/**
 * River.cpp , all functions are explained in River.h .
 */
River::River(const std::string& name) : Area(name) {}

void River::groupArrive(const string& group_name, const string& clan,
                           map<string, Clan>& clan_map) {
    Area::groupArrive(group_name,clan,clan_map);
    GroupPointer arrived_group = clan_map.at(clan).getGroup(group_name) ;
    sortGroupsByStrongest();
    for(unsigned int i=0 ; i<groups.size() ; i++){
      if (clan_map.at(clan).isFriend(clan_map.at((*(groups[i])).getClan()))) {
          if ((*arrived_group).trade(*(groups[i]))) {
                break  ; //trade succeeded
          }
      }
    }
    groups.insert(groups.begin(),arrived_group);
}

