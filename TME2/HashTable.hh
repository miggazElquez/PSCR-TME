#pragma once

#include <forward_list>
#include <vector>
#include <utility>


using namespace std;

namespace tme {



template<typename K, typename V>
class Entry {
public:
	K key;
	V value;
	Entry(K k,V v):key(k),value(v){};
};


template<typename K, typename V>
class HashTable {


public:
	size_t size;
	std::vector<forward_list<Entry<K,V>>> buckets;

	HashTable(int size) :size(size),buckets(size){};


	V* get(const K & key) {
		size_t h = std::hash<K>()(key);

		auto& l = buckets[h % size];
		for (auto& e: l) {
			if (e.key == key) {
				return &e.value;
			}
		}
		return nullptr;
	}

	bool put (const K & key, const V & value) {
		auto val = get(key);
		if (val) {
			*val = value;
			return true;
		}

		size_t h = std::hash<K>()(key);
		auto& l = buckets[h % size];
		Entry e(key,value);
		l.push_front(e);

		return false;

	}

};

}