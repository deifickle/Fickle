
// defines a function pointer with the string FPtr appended to the name...
#define BUNTING_DECLARE_FUNCTION_PTR(ret, name, ...)                     \
	typedef ret(__cdecl * name##FPtr)(__VA_ARGS__); \
	extern name##FPtr       name;


// Swaps the provided pointers
#define BUNTING_SWAP_POINTERS(type, x, y) \
    {                          \
        type t;                \
        t = x;                 \
        x = y;                 \
        y = t;                 \
    }