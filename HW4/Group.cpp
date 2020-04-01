#include "Group.h"
using namespace mtm;
using  std::ostream ;
using std::endl;

/**
 * Group.cpp
 * All Functions have explanation in Group header file .
 */
Group::Group(const std::string& name, const std::string& clan,int children
        ,int adults, int tools, int food, int morale) : group_name(name)
        ,clan_name(clan) , children(children), adults(adults)
        ,tools(tools),food(food),morale(morale){
    if (!this->checkParameters()) {
        throw GroupInvalidArgs();
    }
}

Group::Group(const std::string& name, int children, int adults) :
        group_name(name),clan_name(""),children(children)
        ,adults(adults),tools(4*adults),food(3*adults+2*children)
        ,morale(70){
    if (!this->checkParameters()) {
        throw GroupInvalidArgs();
    }
}

const std::string& Group::getName() const{
    return group_name ;
}

int Group::getSize() const{
    return children+adults ;
}

const std::string& Group::getClan() const{
    return clan_name;
}

void Group::changeClan(const std::string& clan){
    if (clan_name==clan) {//if clans are equal do nothing.
        return ;
    }
    if (clan_name.empty()) { //means there was no clan assigned to group.
        if ((morale + floor(morale*0.1)) >=100){
            morale=100;
        } else {
            morale = morale + floor(morale*0.1) ;
        }
    } else {//means there was an assigned clan to the group.
        if (((morale - floor(morale * 0.1) <= 0))) {
            morale = 0;
        } else {
            morale = morale - floor(morale * 0.1);
        }
    }
    clan_name=clan;
}

bool Group::operator<(const Group& rhs) const{
    int res = getPower() - rhs.getPower() ;
    if (res>0){
        return false;
    }
    if (res<0){
        return true;
    }
    if (group_name<rhs.getName()) {
        return true;
    }
    return false;
}

bool Group::operator>(const Group& rhs) const{
    int res = getPower() - rhs.getPower() ;
    if (res>0){
        return true;
    }
    if (res<0){
        return false;
    }
    if (group_name>rhs.getName()) {
        return true;
    }
    return false;
}

bool Group::operator<=(const Group& rhs) const{
    return !operator>(rhs);
}

bool Group::operator>=(const Group& rhs) const{
    return !operator<(rhs) ;
}

bool Group::operator==(const Group& rhs) const {
    return (operator>=(rhs))&&(operator<=(rhs));
}

bool Group::operator!=(const Group& rhs) const{
    return (group_name!=rhs.getName())&&(getPower()!=rhs.getPower());
}

bool Group::unite(Group& other, int max_amount){
    if ((clan_name.empty())||(other.getClan().empty())){
        return false ;
    }
    if (clan_name!=other.getClan()||
        ((getSize()+other.getSize())>max_amount)||
        (morale<70)||(other.morale<70)||(this==&other)){
        return false ;
    }
    if (operator<(other)) {
        group_name=other.group_name;
    }
    operator+=(other);
    other.emptyGroup();
    return true;
}

Group Group::divide(const std::string& name){
    if (name.empty()){
        throw GroupInvalidArgs();
    }
    if ((adults<=1)&&(children<=1)) {
        throw GroupCantDivide();
    }
    Group new_gorup(name,clan_name,children/2,adults/2,tools/2
            ,food/2,morale);
    (*this)-=(new_gorup);
    return new_gorup;
}

FIGHT_RESULT Group::fight(Group& opponent){
    if (this==&opponent){
        throw GroupCantFightWithItself();
    }
    if((getSize()==0) || (opponent.getSize()==0)){
        throw GroupCantFightEmptyGroup() ;
    }
    if (operator>(opponent)){
        fightEffects((*this),opponent);
        return WON;
    }
    if (operator<(opponent)){
        fightEffects(opponent,(*this));
        return LOST;
    }
    return DRAW;
}

bool Group::trade(Group& other){
    if (this==&other){
        throw GroupCantTradeWithItself();
    }
    if (((tools==food)||(other.tools==other.food)) ||
        ((tools>food)&&(other.tools>other.food)) ||
        ((food>tools)&&(other.food>other.tools))){
        return false  ;
    }
    if (tools>food) {
        exchangeProducts((*this),other);
    } else {
        exchangeProducts(other,(*this));
    }
    return true;
}

std::ostream& mtm::operator<<(std::ostream& os, const Group& group){
    return os << "Group's name: "<<group.group_name<<endl <<
              "Group's clan: "<<group.clan_name<<endl <<
              "Group's children: "<<group.children<<endl <<
              "Group's adults: "<<group.adults<<endl <<
              "Group's tools: "<<group.tools<<endl <<
              "Group's food: "<<group.food<<endl <<
              "Group's morale: "<<group.morale<<endl ;
}