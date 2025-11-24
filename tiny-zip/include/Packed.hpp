#ifndef PACKED_HPP__
#define PACKED_HPP__

#ifdef __GNUC__
#define START_PACKED __attribute__((packed))
#elif defined(_MSC_VER)
#define START_PACKED __pragma(pack(push, 1)) 
#elif defined(__clang__)
#define START_PACKED KEYWORD __attribute__((packed))
#else 
#error This library doesn't support compiler
#endif

#ifdef __GNUC__
#define END_PACKED
#elif defined(_MSC_VER)
#define END_PACKED __pragma(pack(pop))
#elif defined(__clang__)
#define END_PACKED
#else 
#error This library doesn't support compiler
#endif

#endif // !PACKED_HPP__
