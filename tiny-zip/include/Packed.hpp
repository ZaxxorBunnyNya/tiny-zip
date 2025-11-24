#ifndef PACKED_HPP__
#define PACKED_HPP__

#ifdef __GNUC__
#define PACKED_OUTER(KEYWORD) KEYWORD __attribute__((packed))
#elif defined(_MSC_VER)
#define PACKED_OUTER(KEYWORD) __pragma(pack()) KEYWORD 
#elif defined(__clang__)
#define PACKED_OUTER(KEYWORD) KEYWORD __attribute__((packed))
#else 
#error This library doesn't support compiler
#endif


#endif // !PACKED_HPP__

#define struct_packed PACKED_OUTER(struct)