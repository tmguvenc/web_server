#ifndef LOCK_GUARD_H_
#define LOCK_GUARD_H_

template<typename Mutex>
class LockGuard {
public:
  explicit LockGuard(Mutex& m)
    : mtx(m) {
    mtx.lock();
  }
  ~LockGuard() { mtx.unlock(); }

  LockGuard(const LockGuard&) = delete;
  LockGuard(LockGuard&&) = delete;
  LockGuard& operator=(const LockGuard&) = delete;
  LockGuard& operator=(LockGuard&&) = delete;

private:
  Mutex& mtx;
};

#endif  // !LOCK_GUARD_H_