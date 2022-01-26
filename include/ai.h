#ifndef _AI_H_
#define _AI_H_

#include "entt/entt.hpp"

/* Component for entities that defines their AI. Holds data required
 * for their AI.
 */
struct AI
{
    entt::entity target;
};

#endif //_AI_H_
