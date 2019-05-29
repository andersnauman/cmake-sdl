#ifndef MANAGER_COMPONENT_H_
#define MANAGER_COMPONENT_H_

#include <vector>

namespace Manager {
template <class T>
class Component {
    public:
        void Destroy() {
            for (unsigned int i = 0; i < num_active_; i++) {
                container_[i].Reset();
            }
        };  
        bool Add(unsigned int entityId) {
            if (num_active_ > MAX_OBJECTS) {
                return false;
            }
            container_[num_active_].Initialize();
            container_[num_active_++].SetOwner(entityId);
            return true;
        };
        bool Remove(unsigned int entityId) {
            for (unsigned int i = 0; i < num_active_; i++) {
                if (container_[i].GetOwner() == entityId) {
                    container_[i].Reset();
                    num_active_--;                                      // subtract so we enter the active zone
                    T temp = container_[num_active_];                   // save last active
                    container_[num_active_] = container_[i];            // move the "inactive" object outside the active zone
                    container_[i] = temp;                               // restore last active on the "removed" slot
                    break;
                }
            }
            return true;
        };
        T& Get(unsigned int entityId) {
            for (unsigned int i = 0; i < num_active_; i++) {
                if (container_[i].GetOwner() == entityId) {
                    return container_[i];
                }
            }
            //return nullptr;
            return container_[0];
        };
        void GetAllActive(std::vector<T>& obj) {
            obj.clear();
            obj.insert(obj.begin(), container_, container_ + num_active_);
            //for (unsigned int i = 0; num_active_; i++) {
            //    obj.insert(container_[i]);
            //}
        }
        void Update() {
            for (unsigned int i = 0; i < num_active_; i++) {
                container_[i].Update();
            }
        };

    private:
        static const int MAX_OBJECTS = 100;
        unsigned int num_active_ = 0;
        static T container_[MAX_OBJECTS];
};
template <class T>
T Component<T>::container_[Component::MAX_OBJECTS];
};

#endif // MANAGER_COMPONENT_H_