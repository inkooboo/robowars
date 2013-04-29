#ifndef SPINLOCK_HPP
#  define SPINLOCK_HPP

#include <atomic>
#include <chrono>
#include <thread>

/// spinlock from boost examples

class spinlock_t {
private:
  typedef enum {Locked, Unlocked} LockState;
  std::atomic<LockState> state_;

public:
  spinlock_t() : state_(Unlocked) {}

  void lock()
  {
    while (state_.exchange(Locked, std::memory_order_relaxed) == Locked) {
    }
    std::atomic_thread_fence(std::memory_order_acquire);
  }
  void unlock()
  {
    state_.store(Unlocked, std::memory_order_release);
  }
};


#endif // SPINLOCK_HPP
