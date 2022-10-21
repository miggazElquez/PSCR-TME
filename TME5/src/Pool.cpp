#include "Pool.h"
#include "Queue.h"
#include "Job.h"

namespace pr {


	void func(Queue<Job>& q, int id) {
		while (true) {
			Job* j = q.pop();
			if (j == nullptr) {
				break;
			}
			j->run();
			delete j;
		}
	}

	Pool::Pool(int qsize) :queue(qsize){
	}

	void Pool::start(int nbthread) {
		for (int i=0;i<nbthread;i++) {
			threads.emplace_back(func,std::ref(queue),i);
		}
	}

	void Pool::stop() {
		queue.set_non_blocking();
		for (auto it =threads.begin(); it != threads.end();it++) {
			it->join();
		}
	}

	void Pool::submit(Job * job) {
		queue.push(job);
	}

	Pool::~Pool(){}

}