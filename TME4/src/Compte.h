#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	mutable std::recursive_mutex m;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;
	inline void lock() const {m.lock();}
	inline void unlock() const {m.unlock();};
	inline bool try_lock() const {return m.try_lock();};
};

}
