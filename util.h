// Miscellaneous utility functions

#define IS_POWER2(x)  (((x)&((x)-1)) == 0)

extern void error(const char* fmt, ...);
extern void error(token *tkn, const char* fmt, ...);
extern void error(int line, int pos, const char* file, const char* fmt, ...);

extern void warning(const char* fmt, ...);
extern void warning(token *tkn, const char* fmt, ...);
extern void warning(int line, int pos, const char* file, const char* fmt, ...);

extern "C" int strincmp(const char* sq, const char* s2, int n);
extern "C" char* strupper(const char* s);
