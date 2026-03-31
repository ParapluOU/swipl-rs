/* SWI-Prolog >= 9.3 changed many function return types from int to bool.
 * The swipl crate code expects c_int returns (comparing with != 0 / == 0).
 * Override stdbool.h's bool (_Bool) with int so bindgen generates c_int
 * bindings, preserving compatibility with the existing Rust code.
 */
#include <stdbool.h>
#undef bool
#define bool int
#include <SWI-Stream.h>
#include <SWI-Prolog.h>
#undef bool
