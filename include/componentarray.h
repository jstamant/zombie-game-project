#ifndef _COMPONENT_H_
#define _COMPONENT_H_
//NEED TO RENAME TO COMPONONENTARRAY

#include <array>
#include "defines.h"
#include <unordered_map>

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray: public IComponentArray
{
public:
    void insertData(Entity entity, T component) {
        //assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");
        // Put new entry at end and update the maps
        size_t newIndex = size_;
        entityToIndexMap_[entity] = newIndex;
        indexToEntityMap_[newIndex] = entity;
        componentArray_[newIndex] = component;
        size_++;
    }
    void removeData(Entity entity) {
        //assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");
        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = entityToIndexMap_[entity];
        size_t indexOfLastElement = size_ - 1;
        componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];
        // Update map to point to moved spot
        Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
        entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;
        entityToIndexMap_.erase(entity);
        indexToEntityMap_.erase(indexOfLastElement);
        size_--;
    }
    T& getData(Entity entity) {
        //assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");
        // Return a reference to the entity's component
        return componentArray_[entityToIndexMap_[entity]];
    }
    void entityDestroyed(Entity entity) override {
        //Implementation here to avoid linker error
        if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
        {
            // Remove the entity's component if it existed
            removeData(entity);
        }
    }
private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> componentArray_;
    // Map from an entity ID to an array index.
    std::unordered_map<Entity, size_t> entityToIndexMap_;
    // Map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> indexToEntityMap_;
    // Total size of valid entries in the array.
    size_t size_;
};

#endif //_COMPONENT_H_
