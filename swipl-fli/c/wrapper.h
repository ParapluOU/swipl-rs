/* SWI-Prolog >= 9.3 changed many function return types from int to bool.
 * The swipl crate code expects c_int returns (comparing with != 0 / == 0).
 * Redefine bool as int before including headers so bindgen generates c_int
 * bindings, preserving compatibility with the existing Rust code.
 */
#define bool int
#include <SWI-Stream.h>
#include <SWI-Prolog.h>
#undef bool
