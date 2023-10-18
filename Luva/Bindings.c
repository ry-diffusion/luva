#include <lean/lean.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

static lean_external_class *gLoopClass = NULL;

inline static void noop_foreach(void *mod, b_lean_obj_arg fn)
{
}

static void finalizeLoop(void *pLoop)
{
        assert(pLoop);

        uv_loop_close((uv_loop_t *)pLoop);
}

LEAN_EXPORT lean_object *luvaCreateLoop()
{
        uv_loop_t *loop = malloc(sizeof(uv_loop_t));
        assert(loop);
        uv_loop_init(loop);
        return lean_io_result_mk_ok(lean_alloc_external(gLoopClass, loop));
}

LEAN_EXPORT lean_obj_res luvaInitializeNative()
{
        gLoopClass = lean_register_external_class(finalizeLoop, noop_foreach);

        return lean_io_result_mk_ok(lean_box(0));
}