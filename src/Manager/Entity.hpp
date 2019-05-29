#ifndef MANAGER_ENTITY_H_
#define MANAGER_ENTITY_H_

#include <assert.h>

namespace Manager {
class Entity {
    public:
        struct Object {
            unsigned int id_;
            static unsigned int next_id_;
            Object() {
                id_ = next_id_++;
            };
            unsigned int GetId() {
                return id_;
            };
            void Reset() {};
            void Update() {};
        };
        unsigned int Add() {
            assert(num_active_ <= MAX_ENTITIES);
            Object newEntity = container_[num_active_++];
            return newEntity.GetId();
        };
        bool Remove(unsigned int entityId) {
            for (unsigned int i = 0; num_active_; i++) {
                if (container_[i].GetId() == entityId) {
                    container_[i].Reset();
                    num_active_--;                                      // subtract so we enter the active zone
                    Object temp = container_[num_active_];    // save last active
                    container_[num_active_] = container_[i];            // move the "inactive" object outside the active zone
                    container_[i] = temp;                               // restore last active on the "removed" slot
                    return true;
                }
            }
            return false;
        };
        void Update() {
            for (unsigned int i = 0; i < num_active_; i++) {
                container_[i].Update();
            }
        };

    private:
        static const int MAX_ENTITIES = 100;
        unsigned int num_active_ = 0;
        Object container_[MAX_ENTITIES];
};
};
namespace Manager {
unsigned int Entity::Object::next_id_ = 1;
};

#endif // MANAGER_ENTITY_H_