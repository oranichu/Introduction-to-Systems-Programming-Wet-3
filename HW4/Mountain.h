#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "Area.h"

namespace mtm{
    /**
     * Mountain
     */
    class Mountain : public Area {
        GroupPointer ruler ;
        /**
         * A private function that help us who is the strongest group in the
         * area after the ruler (ruler is deleted first) , first searches for
         * the strongest group in the Clan if there's no one it'll return
         * the strongest group that doesn't belong to the clan .
         * @param
         * clan_name - the groups clan name .
         * @return
         * nullptr - if theres no more groups in the area .
         * A pointer to the strongest to belong to the clan - if theres one .
         * A pointer to the strongest group from any clan otherwize .
         */
        GroupPointer findStrongestGroup(const std::string& clan_name) {
            if (groups.size()==0){
                return nullptr;
            }
            sortGroupsByStrongest();
            for (unsigned int i = 0; i < groups.size(); i++) {
                if ((*(groups[i])).getClan() == clan_name) {
                    if ((*(groups[i])).getSize() != 0) {
                            return groups[i];
                        }
                    }
                }
            return groups[0];//returns the strongest group that doesn't belong
            // to the clan , we checked size so this exists for sure .
        }

    public:
        /**
       * Constructor
       * @param
       * name - The name of the mountain area
       * @throws
       * AreaInvalidArguments - If the name is empty.
       */
        explicit Mountain(const std::string& name) ;

        /**
         * Destructor
         */
        ~Mountain() = default;

        /**
         * GroupArrive function .
         * When a group arrives to a Mountain it's need to fight the local
         * ruler (if it's from a diffrenent clan) , if they win they become
         * the ruler , if the ruler's clan is the same as the arriving group
         * and the arriving group is stronger than the ruler group they will
         * switch places .
         * @param
         * group_name - the name of the arrived group.
         * clan - the name of it's Clan .
         * clan_map - the clan map that contains all the clans .
         */
        void groupArrive(const string& group_name, const string& clan,
                         map<string, Clan>& clan_map) ;
        /**
         * GroupLeave function.
         * When a group leaves a mountain the mountain should have a ruler .
         * So if the group was a ruler it finds the strongest group in it's clan
         * or if there no such group leaves it to the strongest group in general
         * (that is in the area) if no more groups left there will be no ruler.
         * if the groups wasn't a ruler nothing will happen.
         * @param
         * group_name - the name of the group that leaves .
         */
        void groupLeave(const std::string& group_name);
    };

}

#endif //MOUNTAIN_H
