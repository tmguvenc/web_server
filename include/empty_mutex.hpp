#ifndef EMPTY_MUTEX_HPP_
#define EMPTY_MUTEX_HPP_

class EmptyMutex {
public:
  void lock() {}
  void unlock() {}
};

#endif // !EMPTY_MUTEX_HPP_