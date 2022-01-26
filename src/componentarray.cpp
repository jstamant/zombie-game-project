//#include "componentarray.h"
//#include "defines.h"

//IMPLEMENTATION IN HEADER FILE
// template<typename T>
// void ComponentArray<T>::insertData(Entity entity, T component)
// {
//     //assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

//     // Put new entry at end and update the maps
//     size_t newIndex = size_;
//     entityToIndexMap_[entity] = newIndex;
//     indexToEntityMap_[newIndex] = entity;
//     componentArray_[newIndex] = component;
//     size_++;
// }

// template<typename T>
// void ComponentArray<T>::removeData(Entity entity)
// {
//     //assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

//     // Copy element at end into deleted element's place to maintain density
//     size_t indexOfRemovedEntity = entityToIndexMap_[entity];
//     size_t indexOfLastElement = size_ - 1;
//     componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];

//     // Update map to point to moved spot
//     Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
//     entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
//     indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;

//     entityToIndexMap_.erase(entity);
//     indexToEntityMap_.erase(indexOfLastElement);

//     size_--;
// }

// template<typename T>
// T& ComponentArray<T>::getData(Entity entity)
// {
//     //assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

//     // Return a reference to the entity's component
//     return componentArray_[entityToIndexMap_[entity]];
// }

//IMPLEMENTATION IN THE HEADER FILE
// template<typename T>
// void ComponentArray<T>::entityDestroyed(Entity entity)
// {
//     if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
//     {
//         // Remove the entity's component if it existed
//         removeData(entity);
//     }
// }
