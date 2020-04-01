#ifndef MTM4_SET_H
#define MTM4_SET_H

#include "exceptions.h"

namespace mtm{
    
    /**
     * A set
     * @tparam Type The type of an element on the group.
     *      Required to implement:
     *                             - operator ==
     *                             - copy constructor
     */
    template<typename Type>
    class MtmSet{
        int setSize;
        /**
         * A node in the set
         */
        class Node{
            Type element;
            Node *next;
        public:
            Node() : element(), next(){}
            explicit Node(const Type& el) : element(el), next(NULL){}
            Node(const Node& node) : element(node.element), next(NULL){}
            ~Node() = default;
            Node* getNext(){
                return next;
            }
            void setNext(Node* node){
                next = node;
            }
            Type& getElement(){
                return element;
            }
        };
        Node* head;

        /**
         * find the node before the one who contains the element argument.
         * the function work only if the set contains the element and it is not
         * in the first place.
         * @param element - the element we search for.
         * @return pointer to the spoken node or NULL if the element is not in
         * the set.
         */
        Node* getBefore(const Type& element){
            Node* itr = head;
            for (int i = 0; i < setSize - 1; ++i) {
                if(itr->getNext()->getElement() != element){
                    itr = itr->getNext();
                } else {
                    return itr;
                }
            }
            return itr;
        }

    public:
        //Forward declaration
        class const_iterator;

        /**
         * A iterator for Set
        */
        class iterator{

            Node *ptr;

            Node* getPtr() const {
                return ptr;
            }

        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            iterator() : ptr(NULL) {}
            
            /**
             * Constructor of Set iterator
             * @param node The node the iterator points to
             */
            explicit iterator(Node *node) : ptr(node){}
            
            /**
             * Copy constructor
             * @param it The iterator to copy
             */
            iterator(const iterator& it) : ptr(it.getPtr()){}

            /**
             * Destructor
             */
            ~iterator() = default;

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this iterator.
             */
            iterator& operator=(const iterator& rhs){
                ptr = rhs.getPtr();
                return *this;
            }
            
            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type& operator*() const{
                if(!ptr){
                    throw NodeIsEndException();
                }
                return ptr->getElement();
            }
            
            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the iterator
             *  points to.
             * C++ use the -> operator on the returned pointer,
             * this allows the user to treat the iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const{
                if(!ptr){
                    throw NodeIsEndException();
                }
                return &(ptr->getElement());
            }
            
            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator& operator++(){
                if(!ptr){
                    throw NodeIsEndException();
                }
                ptr = ptr->getNext();
                return *this;
            }
            
            /**
             * Postfix increment operator (i++)
             * @return iterator that points to the same node as this before
             * the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator operator++(int){
                if(!ptr){
                    throw NodeIsEndException();
                }
                iterator it(*this);
                ++(*this);
                return it;
            }

            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators point to the same node
             */
            bool operator==(const const_iterator& rhs) const{
                return (const_iterator(*this) == rhs);
            }
            
            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators don't point to the same node
             */
            bool operator!=(const const_iterator& rhs) const{
                return !(*this == rhs);
            }

            friend class const_iterator;
        };

    public:
        /**
         * A const_iterator for Set
        */
        class const_iterator{
            Node* ptr;
            Node* getPtr() const {
                return ptr;
            }

        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            const_iterator() : ptr(NULL) {}
            
            /**
             * Constructor of Set const_iterator
             * @param node The node the const_iterator points to
             */
            explicit const_iterator(Node *node) : ptr(node){}
            
            /**
             * Copy constructor
             * @param it The const_iterator to copy
             */
            const_iterator(const const_iterator& it) : ptr(it.getPtr()){}
            
            /**
             * Constructor from iterator (not const_iterator)
             * Allows casting from iterator to const_iterator
             * @param it The iterator to "copy" to a const_iterator
             */
            const_iterator(const iterator& it) : ptr(it.getPtr()){}

            /**
             * Destructor
             */
            ~const_iterator() = default;

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this const_iterator.
             */
            const_iterator& operator=(const const_iterator& rhs){
                ptr = rhs.getPtr();
                return *this;
            }
            
            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the const_iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type& operator*() const{
                if(!ptr){
                    throw NodeIsEndException();
                }
                return ptr->getElement();
            }
            
            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the const_iterator
             *  points to.
             *  C++ use the -> operator on the returned pointer,
             *  this allows the user to treat the const_iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const{
                if(!ptr){
                    throw NodeIsEndException();
                }
                return &(ptr->getElement());
            }
            
            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator& operator++(){
                if(!ptr){
                    throw NodeIsEndException();
                }
                ptr = ptr->getNext();
                return *this;
            }
            
            /**
             * Postfix increment operator (i++)
             * @return const_iterator that points to the same node as this
             * before the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator operator++(int){
                if(!ptr){
                    throw NodeIsEndException();
                }
                const_iterator c_it = *this;
                ++(*this);
                return c_it;
            }
            
            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators point to the same node
             */
            bool operator==(const const_iterator& rhs) const{
                return (ptr == rhs.getPtr());
            }
            
            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators don't point to the same
             * node
             */
            bool operator!=(const const_iterator& rhs) const{
                return !(*this == rhs);
            }
        };
        
        /**
         * Empty constructor
         * Creates an empty set
         */
        MtmSet() : setSize(0), head(NULL){}
        
        /**
         * Copy constructor
         * @param set the Set to copy
         */
        MtmSet(const MtmSet& set) : setSize(0), head(NULL){
            const_iterator c_it(set.begin());
            for (int i = 0; i < set.size(); ++i) {
                insert(*(c_it++));
            }
        }
        
        /**
         * Destructor
         * Free all allocated memory in the set.
         */
        ~MtmSet(){
            while (head){
                Node* curr = head;
                head = head->getNext();
                delete(curr);
            }
        }
        
        /**
         * Insert a new element to the set, doesn't insert if there is already
         *  an equal element in the set.
         * If an element was't inserted, all iterators should stay valid.
         * @param elem The element to insert to the set
         * @return An iterator to the inserted element, or to the equal
         * element if the element wasn't inserted.
         */
        iterator insert(const Type& elem){
            if (find(elem) != const_iterator(NULL)){
                return find(elem);
            }
            Node *temp = new Node(elem);
            temp->setNext(head);
            head = temp;
            setSize++;
            return iterator(temp);
        }

        /**
         * Remove an element from the set. If there is no element equal to
         *  elem in the set, does nothing.
         * If an element wasn't removed, all iterators should stay valid.
         * @param elem the element to remove.
         */
        void erase(const Type& elem){
            if(contains(elem)){
                if(head->getElement() == elem){
                    Node* temp = head;
                    head = head->getNext();
                    delete(temp);
                } else {
                    Node* before = getBefore(elem);
                    Node* temp = before->getNext();
                    before->setNext(temp->getNext());
                    delete(temp);
                }
                setSize--;
            }
        }
        
        /**
         * Remove the element the iterator points to from the set.
         * Iterator to another set is undefined.
         * @param it The iterator to the element to the set.
         */
        void erase(const iterator& it){
            erase(*it);
        }
        
        /**
         * Get the amount of elements in the set.
         * @return The amount of elements in the set.
         */
        int size() const{
            return setSize;
        }
        
        /**
         * Check if the set is empty.
         * @return true is the set is empty.
         */
        bool empty() const{
            return (setSize == 0);
        }
        
        /**
         * Empty the set, free all allocated memory in the set.
         */
        void clear(){
            while (setSize > 0){
                erase(head->getElement());
            }
        }
        
        /**
         * Get an iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        iterator begin(){
            return iterator(head);
        }
        
        /**
         * Get a const_iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        const_iterator begin() const{
            return const_iterator(head);
        }
        
        /**
         * Returns an iterator referring to the past-the-end element in the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return Iterator to past-the-end element.
         */
        iterator end(){
            return iterator(NULL);
        }
        
        /**
         * Returns a const_iterator referring to the past-the-end element in
         * the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return const_iterator to past-the-end element.
         */
        const_iterator end() const{
            return const_iterator(NULL);
        }
        
        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return An iterator that points to the elem.
         */
        iterator find(const Type& elem){
            iterator it = this->begin();
            Node node(elem);
            iterator element(&node);
            for (int i = 0; i < setSize; ++i) {
                if(*it == *element){
                   return it;
                }
                it++;
            }
            return it;
        }
        
        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return A const_iterator that points to the elem.
         */
        const_iterator find(const Type& elem) const{
            const_iterator c_it = this->begin();
            Node node(elem);
            const_iterator element(&node);
            for (int i = 0; i < setSize; ++i) {
                if(*c_it == *element){
                    return c_it;
                }
                c_it++;
            }
            return c_it;
        }
        
        /**
         * Check if an element is in the set.
         * @param elem The element to check if it's in the set.
         * @return True if the element is in the set, false otherwise.
         */
        bool contains(const Type& elem) const{
            const_iterator c_f(find(elem));
            const_iterator c_n(NULL);
            return (const_iterator(find(elem)) != const_iterator(NULL));
        }
        
        /**
         * Check if this set is a superset of a given set.
         * Superset: A superset of B if B is a subset of A, that mean's that
         *  A contains all the elements in B.
         * @param subset The set to check if it's a subset.
         * @return True if the given set is a subset of this set.
         */
        bool isSuperSetOf(const MtmSet& subset) const{
            const_iterator c_it = subset.begin();
            for (int i = 0; i < subset.size(); ++i) {
                if(!contains(*c_it)){
                    return false;
                }
                c_it++;
            }
            return true;
        }
        
        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the == operator.
         * @return true if thw two set conatain the same elements, false
         *  otherwise.
         */
        bool operator==(const MtmSet& rhs) const{
            return (this->isSuperSetOf(rhs) && rhs.isSuperSetOf(*this));
        }
        
        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the != operator.
         * @return false if thw two set conatain the same elements, true
         *  otherwise.
         */
        bool operator!=(const MtmSet& rhs) const{
            return !(*this == rhs);
        }
        
        /**
         * Insert all the elements in the given set to this set (union).
         * @param set The set to insert all the elements from.
         * @return A reference to this set.
         */
        MtmSet& unite(const MtmSet& set){
            const_iterator c_it = set.begin();
            for (int i = 0; i < set.size(); ++i) {
                if(!contains(*c_it)){
                    insert(*c_it);
                }
                c_it++;
            }
            return *this;
        }
        
        /**
         * Returns a new set that is an union of this set, and a given set.
         * @param set The other set (other than this) to be in the union.
         * @return The new set.
         */
        MtmSet unite(const MtmSet& set) const{
            MtmSet newSet(*this);
            newSet.unite(set);
            return newSet;
        }
        
        /**
         * Remove all the elements from this set, that are in the given set
         * (intersection).
         * @param set The other set in the intersection.
         * @return A reference to this set.
         */
        MtmSet& intersect(const MtmSet& set){
            const_iterator c_it = begin();
            int size = setSize;
            for (int i = 0; i < size; ++i) {
                if(!set.contains(*c_it)){
                    erase(*c_it);
                    c_it = begin();
                } else {
                    c_it++;
                }
            }
            return *this;
        }
        
        /**
         * Returns a new set that is an intersection of this set,
         *  and a given set.
         * @param set The other set (other than this) to be in the intersection.
         * @return The new set.
         */
        MtmSet intersect(const MtmSet& set) const{
            MtmSet newSet = *this;
            newSet.intersect(set);
            return newSet;
        }
        
        /**
         * Remove all the elements in the set, that doesn't meet a given
         *  condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A reference to this set.
         */
        template<typename func>
        MtmSet& getSubSet(func condition){
            iterator it = begin();
            int size = setSize;
            for (int i = 0; i < size; ++i) {
                if(!condition(*it)){
                    erase(it);
                    it = begin();
                } else {
                    it++;
                }
            }
            return *this;
        }
        
        /**
         * Get a subset of this set, that contains all the elements in the set,
         * that doesn't meet a given condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A the new set.
         */
        template<typename func>
        MtmSet getSubSet(func condition) const{
            MtmSet newSet = *this;
            newSet.getSubSet(condition);
            return newSet;
        }
    };
} // namespace mtm

#endif //MTM4_SET_H
