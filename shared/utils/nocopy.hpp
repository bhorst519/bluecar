#ifndef NOCOPY_HPP
#define NOCOPY_HPP

#define NODEFAULT_NOCOPY_NOMOVE(T) \
   T() = delete; \
   T(const T &) = delete; \
   const T& operator=(const T &) = delete; \
   T(T &&) = delete; \
   const T& operator=(T &&) = delete

#define NOCOPY_NOMOVE(T) \
   T(const T &) = delete; \
   const T& operator=(const T &) = delete; \
   T(T &&) = delete; \
   const T& operator=(T &&) = delete

#define NOMOVE(T) \
   T(T &&) = delete; \
   T& operator=(T &&) = delete

#endif  // NOCOPY_HPP
