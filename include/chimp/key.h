#ifndef CHIMP_KEY_H
#define CHIMP_KEY_H

#include "chimp/common.h"

namespace chimp {

/**
 * Key pass idiom guard.
 *
 * This class allows implementing key pass idiom. It is used
 * for example by Arg to allow some methods to be called only by App.
 * For more information about key pass pattern see:
 * [https://stackoverflow.com/a/3218920/13078067](https://stackoverflow.com/a/3218920/13078067).
 */
template <typename T> class Key final {
private:
  friend T;

  // XXX: We **must** explicitly provide user-provided default constructor
  // (in contrast to making it = default;) because otherwise c++11, c++14
  // and c++17 standards would treat this class as a *aggregate* class
  // and by using aggregate initialization anybody could create an instance of
  // this class, which would utterly defeat the whole purpose of this guard.
  Key() {}

  // Copying and cloning is disabled to enforce stricter usage rules.
  Key(const Key&) = delete;
  Key(Key&&) = delete;
  Key& operator=(const Key&) = delete;
  Key& operator=(Key&&) = delete;

  // Destructor is private to prevent class T from leaking key.
  ~Key() = default;
};

} // namespace chimp

#endif // CHIMP_KEY_H
