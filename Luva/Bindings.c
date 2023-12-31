#include <lean/lean.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define Function LEAN_EXPORT lean_object *
static lean_external_class *gLoopClass = NULL;

inline static void noop_foreach(void *mod, b_lean_obj_arg fn)
{
}

static void finalizeLoop(void *pLoop)
{
        assert(pLoop);

        uv_loop_close((uv_loop_t *)pLoop);
        free(pLoop);
}

Function luvaCreateLoop()
{
        uv_loop_t *loop = malloc(sizeof(uv_loop_t));
        assert(loop);

        uv_loop_init(loop);
        return lean_io_result_mk_ok(lean_alloc_external(gLoopClass, loop));
}

Function luvaRunLoop(lean_object *obj, lean_object *obj2)
{
        uv_loop_t *L = lean_get_external_data(obj);
        unsigned int runMode = lean_unbox_uint32(obj2);

        return lean_io_result_mk_ok(lean_box_uint32(uv_run(L, runMode)));
}

LEAN_EXPORT lean_obj_res luvaInitializeNative()
{
        gLoopClass = lean_register_external_class(finalizeLoop, noop_foreach);

        return lean_io_result_mk_ok(lean_box(0));
}