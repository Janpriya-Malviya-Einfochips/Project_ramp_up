#include <assert.h>
#include <iostream>

typedef int& IntLRef;
typedef IntLRef& IntLLRef;
typedef IntLRef&& IntLRRef;

typedef int&& IntRRef;
typedef IntRRef& IntRLRef;
typedef IntRRef&& IntRRRef;

template<typename T, typename U>
struct IsSameType
{
  static const bool value = false;
};

template<typename T>
struct IsSameType <T, T>
{
  static const bool value = true;
};

int main()
{
  static_assert(IsSameType<IntLRef, IntLLRef>::value, "LRef DIF LLRef");
  static_assert(IsSameType<IntLRef, IntLRRef>::value, "LRef DIF LRRef");
  static_assert(IsSameType<IntLLRef, IntLRRef>::value, "LRef DIF LRRef");
  static_assert(IsSameType<IntRRef, IntRLRef>::value, "RRef DIF RLRef");
  static_assert(IsSameType<IntRRef, IntRRRef>::value, "RRef DIF RRRef");
  static_assert(IsSameType<IntRLRef, IntRRRef>::value, "RLRef DIF RRRef");
  static_assert(IsSameType<IntLRef, IntRRef>::value, "LRef DIF RRef");
  static_assert(IsSameType<IntLRef, IntRLRef>::value, "LRef DIF RLRef");
  static_assert(IsSameType<IntLRRef, IntRRRef>::value, "LRRef DIF RRRef");
  return 0;
}
