#ifndef MTM4_AREA_H
#define MTM4_AREA_H

#include <string>
#include <map>
#include "Clan.h"
#include "Group.h"
#include <vector>
#include <memory>
#include <algorithm>

using std::string;
using std::shared_ptr;
using std::map;

namespace mtm{
    
    /**
     * An abstract call of an area in the world.
     * Assume every name is unique.
     * Groups that become empty, should be removed from the area.
     */
    class Area{
        std::string area_name ;
        MtmSet<std::string> reachable_areas ;
    protected:
        std::vector<GroupPointer> groups;

        /**
         * static bool function to help us with sorting the groups pointer
         * vector by the strogest group first .
         * @param
         * p1 - the first group pointer .
         * p2 - the second group pointer .
         * @return
         * true - if the first group is stronger than the second .
         * false - otherwize .
         */
        static bool sortFunction(const GroupPointer& p1,const GroupPointer& p2){
            return (*p1)>(*p2) ;
        }

        /**
         * A void function that sorts the groups in the area by strongest first.
         */
        void sortGroupsByStrongest() {
            std::sort(groups.begin(), groups.end(), sortFunction);
        }

        /**
         * A function that helps us find a group in the Area and returns it's
         * place in the groups vector.
         * @param
         * group_name - the group name that we wish to check.
         * @return
         * the group index in the vector - if the group was found in all
         * the gorups in the Area ,
         * -1 - otherwize.
         */
        int findGroup(const std:: string& group_name){
            for(unsigned int i=0 ; i<groups.size() ; i++){
                if ((*(groups[i])).getName() == group_name) {
                    return i ;
                }
            }
            return -1 ;
        }
        /**
         * A private function that helps us delete any empty groups after a
         * fight or after a unite.
         */
        void deleteEmptyGroups () {
            for(unsigned int i=0 ; i<groups.size() ; i++){
                if ((*(groups[i])).getName().empty()) {
                    groups.erase(groups.begin()+i);
                }
            }
        }

    public:
        /**
         * Constructor
         * @param name The name of the area
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit Area(const std::string& name) ;
        
        /**
         * Disable copy constructor
         */
        Area(const Area&) = delete;

        /**
         * Disable assignment operator
         */
        Area &operator=(const Area &) = delete;

        /**
         * Destructor
         */
        virtual ~Area() = default;
        
        /**
         * Add an area, that can be reachable from this area.
         * Doesn't mean that this area is reachable from the area with the
         * given name.
         * @param area_name The name of the area that can be reachable from
         *  this are.
         */
        void addReachableArea(const std::string& area_name);
        
        /**
         * Check if an area is reachable from this area.
         * An area is always reachable from itself.
         * @param area_name The name of the area to check if it's reachable.
         * @return True if the area with the given name is reachable from
         * this area, and false otherwise.
         */
        bool isReachable(const std::string& area_name) const;
        
        /**
         * Get a group into the area.
         * @param group_name The name of the group that get into the area.
         * @param clan The name of the clan that the group belongs to.
         * @param clan_map The map of clans that contains the clan of the group
         * @throws AreaClanNotFoundInMap If there is no clan with the given
         * name in the map.
         * @throws AreaGroupNotInClan If there is no group with the given name
         * in the clan with the given name in the map.
         * @throws AreaGroupAlreadyIn If group with same name already in the
         *  area.
         *
         * Assert that the map does contain the clan that the group belongs to.
         */
        virtual void groupArrive(const string& group_name, const string& clan,
                                 map<string, Clan>& clan_map) ;
        
        /**
         * Get a group out of the area.
         * @param group_name The name of the leaving group.
         * @throws AreaGroupNotFound If there is no group in the area with the
         *  same name;
         */
        virtual void groupLeave(const std::string& group_name);
        
        /**
         * Get a set of the names of all the groups in the area.
         * @return A set that contains the names of all the groups in the area.
         */
        MtmSet<std::string> getGroupsNames() const;
    };
} //namespace mtm

#endif //MTM4_AREA_H
