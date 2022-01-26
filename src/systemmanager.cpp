// #include "defines.h"
// #include <memory>
// #include "systemmanager.h"

// //DEBUG
// #include <iostream>

// SystemManager::SystemManager() {
//     std::cout << "New SystemManager!" << std::endl;
// }

// //TRYING IMPLEMENTATION IN HEADER FILE
// // template<typename T>
// // std::shared_ptr<T> SystemManager::RegisterSystem(void)
// // {
// //     const char* typeName = typeid(T).name();
// //     //assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");
// //     // Create a pointer to the system and return it so it can be used externally
// //     auto system = std::make_shared<T>();
// //     mSystems.insert({typeName, system});
// //     return system;
// // }

// // template<typename T>
// // void SystemManager::SetSignature(Signature signature)
// // {
// //     const char* typeName = typeid(T).name();

// //     //assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

// //     // Set the signature for this system
// //     mSignatures.insert({typeName, signature});
// // }

// void SystemManager::EntityDestroyed(Entity entity)
// {
//     // Erase a destroyed entity from all system lists
//     // mEntities is a set so no check needed
//     for (auto const& pair : mSystems)
//     {
//         auto const& system = pair.second;

//         system->entities_.erase(entity);
//     }
// }

// void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
// {
//     // Notify each system that an entity's signature changed
//     for (auto const& pair : mSystems)
//     {
//         auto const& type = pair.first;
//         auto const& system = pair.second;
//         auto const& systemSignature = mSignatures[type];

//         // Entity signature matches system signature - insert into set
//         if ((entitySignature & systemSignature) == systemSignature)
//         {
//             system->entities_.insert(entity);
//         }
//         // Entity signature does not match system signature - erase from set
//         else
//         {
//             system->entities_.erase(entity);
//         }
//     }
// }
