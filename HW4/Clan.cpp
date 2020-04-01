#include "Clan.h"
#include <list>
using namespace mtm ;
using  std::ostream ;
using std::endl;

Clan::Clan(const std::string& name) : clan_name(name),groups(),friends(){
    if (name.empty()){
        throw ClanEmptyName();
    }
}

void Clan::addGroup(const Group& group){
    if (doesContain(group.getName())) {
        throw ClanGroupNameAlreadyTaken() ;
    }
    if (group.getSize()==0) {
        throw ClanGroupIsEmpty();
    }
    Group new_group(group);
    new_group.changeClan(clan_name);
    GroupPointer new_group_ptr(new Group(new_group)) ;
    groups.insert(new_group_ptr);
}

const GroupPointer& Clan::getGroup(const std::string& group_name) const {
    MtmSet<GroupPointer>::const_iterator c_it = groups.begin();
    for (int i = 0; i < groups.size(); ++i) {
        if ((*(*c_it)).getName() == group_name) {
            return *c_it ;
        }
        c_it++;
    }
    throw ClanGroupNotFound();
}

bool Clan::doesContain(const std::string& group_name) const{
    MtmSet<GroupPointer>::const_iterator c_it = groups.begin();
    for (int i = 0; i < groups.size(); ++i) {
        if ((*(*c_it)).getName() == group_name) {
            return true ;
        }
        c_it++;
    }
    return false;
}

int Clan::getSize() const {
    int clan_size = 0 ;
    MtmSet<GroupPointer>::const_iterator c_it = groups.begin();
    for (int i = 0; i < groups.size(); ++i) {
        clan_size+=(*(*c_it)).getSize() ;
        c_it++;
    }
    return clan_size;
}

Clan& Clan::unite(Clan& other, const std::string& new_name){
    if (new_name.empty()){
        throw ClanEmptyName();
    }
    if ((clan_name==other.clan_name) ||(checkIfGroupIsInOtherClan(other))){
        throw ClanCantUnite();
    }
    clan_name=new_name;
    changeAllGroupsClan(new_name);
    addGroupsFromClan(other);
    other.groups.clear();
    friends.unite(other.friends);
    return (*this);
}

void Clan::makeFriend(Clan& other){
    if (this==&other){
        return ;
    }
    friends.insert(other.clan_name);
    other.friends.insert(clan_name);
}

bool Clan::isFriend(const Clan& other) const{
    if (this==&other){
        return true;
    }
    return friends.contains(other.clan_name) ;
}

std::ostream& mtm::operator<<(std::ostream& os, const Clan& clan){
    int size = clan.groups.size();
    os << "Clan's name: " << clan.clan_name << endl ;
    os << "Clan's groups:"<< endl ;
    MtmSet<GroupPointer>::const_iterator c_it = clan.groups.begin();
    std::list<Group> groupList ;
    for (int i = 0; i < size; ++i) {
        groupList.push_back(*(*c_it));
        c_it++;
    }
    groupList.sort() ;
    for(int i=0 ; i<size ; ++i) {
        if (groupList.back().getSize()!=0) {
            os << groupList.back().getName() << endl;
        }
        groupList.pop_back();
    }
    return os;
}