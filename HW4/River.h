#ifndef RIVER_H
#define RIVER_H

#include "Area.h"

namespace mtm{
    /**
     * River
     */
    class River : public Area {

    public:
        /**
       * Constructor
       * @param
       * name - The name of the river area
       * @throws
       * AreaInvalidArguments - If the name is empty.
       */
        explicit River(const std::string& name)  ;

        /**
         * Destructor
         */
        ~River() = default;

        /**
         * GroupArrive function
         * when a group arrives into a river it need to trade with the strongest
         * group in the area that is a friend of the clan or from the same clan
         * if trade didn't succeded with none of the groups in the area
         * do nothing
         * @param
         * group_name - the name of the group that arrived
         * clan - the clan the group belongs too .
         * clan_map - the map that has all the clans.
         */
        void groupArrive(const string& group_name, const string& clan,
                         map<string, Clan>& clan_map) ;
    };

}

#endif //PLAIN_RIVER_H
