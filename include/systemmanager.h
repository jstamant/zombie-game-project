#ifndef _SYSTEMMANAGER_H_
#define _SYSTEMMANAGER_H_

#include "defines.h"
#include <memory>
#include "system.h"
#include <unordered_map>

//DEBUG
#include <iostream>

class SystemManager
{
public:
    SystemManager();
    template<typename T> std::shared_ptr<T> RegisterSystem(void) {
        //TRYING IMPLEMENTATION HERE INSTEAD OF CPP FILE, OTHERWISE LINKER ISSUES
        const char* typeName = typeid(T).name();
        std::cout << "Registering system: " << typeName << std::endl;
        //assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");
        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        mSystems.insert({typeName, system});
        return system;
    }
    template<typename T> void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();
        //assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");
        // Set the signature for this system
        mSignatures.insert({typeName, signature});
    }
    void EntityDestroyed(Entity);
    void EntitySignatureChanged(Entity, Signature);
private:
    // Map from system type string pointer to a signature
    std::unordered_map<const char*, Signature> mSignatures{};

    // Map from system type string pointer to a system pointer
    std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};

#endif //_SYSTEMMANAGER_H_
