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
		Entry<K,V> e(key,value);
		l.push_front(e);

		return false;

	}


	class Iterator :public std::iterator<std::input_iterator_tag, Entry<K,V>,long,const Entry<K,V>*, Entry<K,V>> {
	private:
		typename std::vector<forward_list<Entry<K,V>>>::iterator cur_b;
		typename std::vector<forward_list<Entry<K,V>>>::iterator end;
		typename forward_list<Entry<K,V>>::iterator cur;

	public:

		//struct iterator_category :  std::input_iterator_tag {};


		//using iterator_category = std::input_iterator_tag;

		Iterator(typename std::vector<forward_list<Entry<K,V>>>::iterator c_b,
			typename std::vector<forward_list<Entry<K,V>>>::iterator e, typename forward_list<Entry<K,V>>::iterator c):
			cur_b(c_b),end(e),cur(c){}

		Iterator operator++() {
			cur++;
			if (cur != cur_b->end()) {
				return *this;
			}
			cur_b++;
			while (cur_b != end) {
				if (cur_b->begin() != cur_b->end()) {
					cur = cur_b->begin();
					break;
				}
				cur_b++;
			}
			return *this;
		}

		bool operator!=(Iterator h) {
			if (cur_b != h.cur_b) {
				return true;
			}
			return (cur != h.cur);
		}

		bool operator==(Iterator h) {
			return !(this != h);
		}


		Entry<K,V> operator*() {
			return *cur;
		}

	};

	Iterator begin() {
		auto it = buckets.begin();
		int i = 0;
		while (it != buckets.end()) {
			std::cout << i << std::endl;
			i++;
			if (it->begin() != it->end()) {
				Iterator h(it,buckets.end(),it->begin());
				return h;
			}
		}
		return end();
	}

	Iterator end() {
		Iterator h(buckets.end(),buckets.end(),buckets[size-1].end());
		return h;
	}




};





}