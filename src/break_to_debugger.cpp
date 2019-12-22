#include <Rcpp.h>
using namespace Rcpp;



// [[Rcpp::export]]
int internal_break_to_debugger()
{
  // DANGEROUS: Works only on x86 instruction set CPUs
  // FIXME: https://stackoverflow.com/questions/4326414/set-breakpoint-in-c-or-c-code-programmatically-for-gdb-on-linux
  // https://stackoverflow.com/questions/3634124/why-does-int-3-generate-a-sigsegv-in-64-bit-instead-of-stopping-the-debugger

  // the surrounding code is just for testing purposes (eg. if the compiler optimizes away some parts)

  // "int 3" is the assembly instruction to create a breakpoint = get the 0xCC single-byte opcode:
  int a = 3;  // just an arbitrary number
  asm("int $3");
  // std::raise(SIGINT);
  // std::raise(SIGTRAP); trap is no symbol -> only for POSIX
  // __debugbreak();  // [Inferior 1 (process 19860) exited with code 020000000003]
  // std::abort() // part of the standard C++ library and is cross-platform but raises SIGABRT which is probably not working on Windows
  // raise(SIGTRAP); // error: 'SIGTRAP' was not declared in this scope
  // __builtin_trap(); // GCC builtin: http://gcc.gnu.org/onlinedocs/gcc-4.3.2/gcc/Other-Builtins.html#index-g_t_005f_005fbuiltin_005ftrap-2760
  a++;      // work-around to provide code after the breakpoint to avoid SEGFAULTS when looking for the next code/statement to execute
  return a;

  // See also:
  // https://stackoverflow.com/questions/37299/xcode-equivalent-of-asm-int-3-debugbreak-halt
  // https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak
  // raise(SIGTRAP); // for most POSIX systems; #include <signal.h>
  // GCC has a builtin function named __builtin_trap
  // https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html

  // https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak
  // https://github.com/nemequ/portable-snippets/blob/master/debug-trap/debug-trap.h

  // https://github.com/scottt/debugbreak/
}
