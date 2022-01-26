// #include <array>
// #include "componentmanager.h"
// #include "defines.h"
// #include <memory>
// #include <unordered_map>

// //DEBUG
// #include <iostream>

// ComponentManager::ComponentManager() {
//     std::cout << "New ComponentManager!" << std::endl;
// }

// //Implementation must be done in the header file to avoid a link error.
// // TODO: figure out how to fix this from the makefile
// // template<typename T>
// // void ComponentManager::RegisterComponent(void) {
// // //    const char* typeName = typeid(T).name();
// // //    std::cout << "Registering component: " << typeName << std::endl;
// //     std::cout << "Registering component: NONE" << std::endl;
// //     //assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");
// //     // Add this component type to the component type map
// //     //mComponentTypes.insert({typeName, mNextComponentType});
// //     // Create a ComponentArray pointer and add it to the component arrays map
// //     //mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
// //     // Increment the value so that the next component registered will be different
// //     //mNextComponentType++;
// // }

// // template<typename T>
// // ComponentType ComponentManager::GetComponentType()
// // {
// //     const char* typeName = typeid(T).name();

// //     //assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

// //     // Return this component's type - used for creating signatures
// //     return mComponentTypes[typeName];
// // }

// //LINKER NEEDS IMPLEMENTATION IN HEADER FILE
// // template<typename T>
// // void ComponentManager::AddComponent(Entity entity, T component)
// // {
// //     // Add a component to the array for an entity
// //     GetComponentArray<T>()->InsertData(entity, component);
// // }

// template<typename T>
// void ComponentManager::RemoveComponent(Entity entity)
// {
//     // Remove a component from the array for an entity
//     GetComponentArray<T>()->RemoveData(entity);
// }

// // template<typename T>
// // T& ComponentManager::GetComponent(Entity entity)
// // {
// //     // Get a reference to a component from the array for an entity
// //     return GetComponentArray<T>()->GetData(entity);
// // }

// void ComponentManager::EntityDestroyed(Entity entity)
// {
//     // Notify each component array that an entity has been destroyed
//     // If it has a component for that entity, it will remove it
//     for (auto const& pair : mComponentArrays)
//     {
//         auto const& component = pair.second;

//         component->entityDestroyed(entity);
//     }
// }
