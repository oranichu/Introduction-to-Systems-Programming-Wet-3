#ifndef PLAIN_PLAIN_H
#define PLAIN_PLAIN_H

#include "Area.h"
#include <sstream>

namespace mtm{
    #define MIN_SIZE_FOR_SPLIT (10)
    /**
     * Plain
     */
    class Plain : public Area {
        /**
         * A private function that helps us unite a group that arrived to the
         * plain and need to unite with the strongest group in the area
         * from the same clan (which is not empty) .
         * @param
         * clan_name - the clan name .
         * third_of_clan - a third of the clan population.
         * group - A pointer to the group we wish to unite.
         */
        void  uniteGroups(const string& clan_name,int third_of_clan
                ,GroupPointer group) {
            sortGroupsByStrongest();
            for (unsigned int i = 0; i < groups.size(); i++) {
                if ((*(groups[i])).getClan() == clan_name) {
                    if ((*(groups[i])).getSize() != 0 ){
                        if ((*groups[i]).unite(*group, third_of_clan)) {
                            return;
                        }
                    }
                }
            }// we didn't fine a group to unite with .
            groups.insert(groups.begin(), group);
        }
        /**
         * A Praivte function that helps us check if a certin group name
         * exiest in one of all the clans.
         * @param
         * clan_map - the map that has the entire list of clans.
         * name - the name of the group that we want to check .
         * @return
         * true - if a group was found with the same name .
         * false - otherwize .
         */
        bool checkIfNameExiest(map<string, Clan>& clan_map,const string& name){
            for (std::map<string,Clan>::iterator it=clan_map.begin();
                    it!= clan_map.end() ; it++) {
                if ((it->second).doesContain(name)){
                    return true ;
                }
            }
            return false ;
        }

        /**
         * A private function that helps us dived a group into 2 groups
         * the other group will have the same name and with a "_i" when
         * i is a number bigger than 2 depending on available names .
         * @param
         * clan - the that the group we will split belongs to .
         * clan_map - the map that hold the entire clans .
         * group - a group pointer to the group we wish to split .
         */
        void divideGroups(const string& clan,map<string, Clan>& clan_map,
                          GroupPointer group) {
            string group_name= (*group).getName();
            std::stringstream temp_name ;
            int index = 2 ;
            do {
                temp_name.str("");
                temp_name.clear();
                temp_name<< group_name << "_" << index++ ;
            }
            while (checkIfNameExiest(clan_map,temp_name.str()));
            Group new_group = (*group).divide(temp_name.str()) ;
            clan_map.at(clan).addGroup(new_group);
            GroupPointer group2 = clan_map.at(clan).getGroup(temp_name.str());
            groups.insert(groups.begin(),group);
            groups.insert(groups.begin(),group2);
        }

    public:
        /**
       * Constructor
       * @param
       * name - The name of the plain area
       * @throws
       * AreaInvalidArguments - If the name is empty.
       */
        explicit Plain(const std::string& name)  ;

        /**
         * Destructor
         */
         ~Plain() = default;


        /**
         * Group Arrive function .
         * when a group arrives to a Plain area we need to check if group size
         * smaller than a third of the clan population , if so we unite her
         * with the strongest group of the same clan that is in the area
         * and toghter they cannot be more than a third of the population aswell
         * (if there is one avilable ) , if the group size is bigger than a
         * third of the clan population we will divide the group to a new group
         * with a new name which will be consited from the old name and + "_i"
         * when i is a number bigger than 2 that will allow the name to be
         * avilable .
         * @param
         * group_name - the name of the group that arrived
         * clan - the clan the group belongs too .
         * clan_map - the map that has all the clans.
         */
        void groupArrive(const string& group_name, const string& clan,
                                 map<string, Clan>& clan_map) ;
    };

}

#endif //PLAIN_PLAIN_H
