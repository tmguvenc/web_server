#ifndef EMPTY_MUTEX_H_
#define EMPTY_MUTEX_H_

class EmptyMutex {
public:
  void lock() {}
  void unlock() {}
};

#endif  // !EMPTY_MUTEX_H_