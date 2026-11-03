#ifndef STORE_H
#define STORE_H


#include <string>
#include <unordered_map>
#include <shared_mutex>

class KeyValueStore {
    private:
        std::unordered_map<std::string, std::string> store;
        mutable std::shared_mutex mutex;

    public:
    void set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& value) const;
    bool remove(const std::string& key);
    size_t size() const;
};

#endif
