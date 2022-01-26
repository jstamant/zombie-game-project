#ifndef _COMPONENTMANAGER_H_
#define _COMPONENTMANAGER_H_

#include "componentarray.h"
#include "defines.h"
#include <memory>
#include <unordered_map>

//DEBUG
#include <iostream>

class ComponentManager
{
public:
    ComponentManager();
    template<typename T> void RegisterComponent(void) {
        //Implementation must be here to avoid a link error
        const char* typeName = typeid(T).name();
        std::cout << "Registering component: " << typeName << std::endl;
        //assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");
        // Add this component type to the component type map
        mComponentTypes.insert({typeName, mNextComponentType});
        // Create a ComponentArray pointer and add it to the component arrays map
        mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        // Increment the value so that the next component registered will be different
        mNextComponentType++;
    }
    template<typename T> ComponentType GetComponentType(void) {
        const char* typeName = typeid(T).name();
        //assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");
        // Return this component's type - used for creating signatures
        return mComponentTypes[typeName];
    }
    template<typename T> void AddComponent(Entity entity, T component) {
        //Implementation must be here to avoid a link error
        const char* typeName = typeid(T).name();
        std::cout << "Adding component " << typeName << " to entity " << entity << std::endl;
        // Add a component to the array for an entity
        GetComponentArray<T>()->insertData(entity, component);
        std::cout << "Added component " << typeName << " to entity " << entity << std::endl;
    }
    template<typename T> void RemoveComponent(Entity);
    template<typename T> T& GetComponent(Entity entity) {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->getData(entity);
    }

    void EntityDestroyed(Entity);
private:
    // Map from type string pointer to a component type
    std::unordered_map<const char*, ComponentType> mComponentTypes{};

    // Map from type string pointer to a component array
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};

    // The component type to be assigned to the next registered component - starting at 0
    ComponentType mNextComponentType{};

    // Convenience function to get the statically casted pointer to the ComponentArray of type T.
    template<typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray(void) {
        //LINKER REQUIRES IMPLEMENTATION HERE
		const char* typeName = typeid(T).name();
        //assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}
};

#endif //_COMPONENTMANAGER_H_
