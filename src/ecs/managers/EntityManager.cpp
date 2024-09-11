#include "EntityManager.hpp"

void EntityManager::Init() 
{
    for (EntityID e = 0; e < MAX_ENTITIES; e++)
    {
        availableEntities.push(e);
        entityStatus[e] = false;
    }
}

bool EntityManager::IsActive(const EntityID entity) const
{
    return entity < MAX_ENTITIES && entityStatus[entity];
}

EntityID EntityManager::CreateEntity() 
{
    if (count < MAX_ENTITIES) 
    {
        const EntityID entity = availableEntities.front();
        availableEntities.pop();
        entityStatus[entity] = true;

        count++;
        return entity;
    }

    throw std::runtime_error("Max entity limit reached");
    
}

void EntityManager::DeleteEntity(const EntityID entity)
{
    if (IsActive(entity))
    {
        availableEntities.push(entity);
        entityStatus[entity] = false;
        count--;
    }
    else 
    {
        fprintf(stderr, "Cannot delete non existent entity");
    }
    
}

size_t EntityManager::GetEntityCount() const
{
    return count;
}

void EntityManager::SetSignature(const EntityID entity, const Signature signature)
{
    if (IsActive(entity)) 
    {
        signatures[entity] = signature;
    }
    else 
    {
        fprintf(stderr, "Cannot set signature on non existent entity");
    }
}

Signature EntityManager::GetSignature(const EntityID entity) const
{
    if (IsActive(entity)) 
    {
        return signatures[entity];
    }

    throw std::runtime_error("Cannot get signature on non existent entity");
}
