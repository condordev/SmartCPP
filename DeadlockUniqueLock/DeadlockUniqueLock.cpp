// https://www.grimm-jaud.de/index.php/blog/gefahren-von-mutexen


#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

struct CriticalData {
	std::mutex mut;
	// other resources which deadlock needs ....
};

void deadLock(CriticalData& a, CriticalData& b) {

	a.mut.lock();
	std::cout << "mutex 1 " << std::this_thread::get_id() << "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	b.mut.lock();
	std::cout << "mutex 2 " << std::this_thread::get_id() << "\n";
	// do something with a and b
	a.mut.unlock();
	b.mut.unlock();

}

int main() {

	CriticalData c1;
	CriticalData c2;

	std::thread t1([&] {deadLock(c1, c2); });
	std::thread t2([&] {deadLock(c2, c1); });

	t1.join();
	t2.join();

}


/*


#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

struct CriticalData{
  std::mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b){

  std::unique_lock<std::mutex>guard1(a.mut,std::defer_lock);
  std::cout << "Thread: " << std::this_thread::get_id() << " first mutex" <<  std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  std::unique_lock<std::mutex>guard2(b.mut,std::defer_lock);
  std::cout << "    Thread: " << std::this_thread::get_id() << " second mutex" <<  std::endl;

  std::cout << "        Thread: " << std::this_thread::get_id() << " get both mutex" << std::endl;
  std::lock(guard1,guard2);
  // do something with a and b
}

int main(){

  std::cout << std::endl;

  CriticalData c1;
  CriticalData c2;

  std::thread t1([&]{deadLock(c1,c2);});
  std::thread t2([&]{deadLock(c2,c1);});

  t1.join();
  t2.join();

  std::cout << std::endl;

}
*/
