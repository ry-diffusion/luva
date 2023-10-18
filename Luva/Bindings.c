#include <lean/lean.h>
#include <string.h>
#include <uv.h>

LEAN_EXPORT lean_object *salude(lean_object *argText)
{
        char str[48] = {0};
        const char *text = lean_string_cstr(argText);

        if (strlen(text) > 36)
        {
                return lean_io_result_mk_error(
                    lean_mk_string("String is too big."));
        }

        sprintf(str, "Hello %s!", text);
        return lean_io_result_mk_ok(lean_mk_string(str));
}
