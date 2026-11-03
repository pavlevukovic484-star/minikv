#include "store.h"
#include <mutex>

void KeyValueStore::set(const std::string& key, const std::string& value) {
    std::unique_lock lock(mutex);
    store[key] = value;
}

bool KeyValueStore::get(const std::string& key, std::string& value) const {
    std::shared_lock lock(mutex);
    auto it = store.find(key);
    if (it != store.end()) {
        value = it->second;
        return true;
    }
    return false;
}

bool KeyValueStore::remove(const std::string& key) {
    std::unique_lock lock(mutex);
    return store.erase(key) > 0;
}

size_t KeyValueStore::size() const {
    std::shared_lock lock(mutex);
    return store.size();
}