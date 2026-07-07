/* SWI-Prolog >= 9.3 changed many function return types (and some struct
 * fields) from `int` to C99 `bool` (`_Bool`, 1 byte).
 *
 * The Rust code in the `swipl` crate treats these as small integers, comparing
 * results with `!= 0` / `== 0`. We therefore want bindgen to generate integer
 * bindings rather than Rust `bool` (which would not compile against `!= 0`).
 *
 * It is NOT safe to map `bool` to `int` here: `_Bool` is a *1-byte* type. On
 * x86-64, a `_Bool`-returning function only sets the low byte (AL) and leaves
 * the upper 24 bits of EAX undefined, so reading the result as a 4-byte `int`
 * yields garbage in the high bytes -> blob/type checks misfire and the FLI
 * misbehaves (e.g. `PL_is_blob` / `PL_get_blob` fail, producing a spurious
 * "tried to raise a var as an exception" panic). It also mis-sizes any struct
 * `bool` field (4 bytes vs 1), corrupting layouts such as `PL_blob_t`.
 * AArch64 happens to zero-extend `_Bool` returns, which is why the `int`
 * mapping appeared to work on Apple Silicon but broke on x86-64 Linux.
 *
 * Mapping `bool` to a 1-byte integer (`unsigned char`) matches `_Bool`'s real
 * size and alignment for both return values and struct fields, while still
 * letting the existing `!= 0` / `== 0` comparisons compile.
 */
#include <stdbool.h>
#undef bool
#define bool unsigned char
#include <SWI-Stream.h>
#include <SWI-Prolog.h>
#undef bool
