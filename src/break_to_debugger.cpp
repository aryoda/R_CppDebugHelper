#include <Rcpp.h>
using namespace Rcpp;



//' @export
// [[Rcpp::export]]
void break_to_debugger()
{
  // DANGEROUS: Works only on x86 instruction set CPUs
  // FIXME: https://stackoverflow.com/questions/4326414/set-breakpoint-in-c-or-c-code-programmatically-for-gdb-on-linux
  // std::abort() // part of the standard C++ library and is cross-platform but raises SIGABRT which is probably not working on Windows
  // https://stackoverflow.com/questions/3634124/why-does-int-3-generate-a-sigsegv-in-64-bit-instead-of-stopping-the-debugger
  // "int 3" is the assembly instruction to create a breakpoint = get the 0xCC single-byte opcode:
  asm("int $3");

  // See also:
  // https://stackoverflow.com/questions/37299/xcode-equivalent-of-asm-int-3-debugbreak-halt
  // https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak
  // raise(SIGTRAP); // for most POSIX systems; #include <signal.h>
  // GCC has a builtin function named __builtin_trap
  // https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
}
