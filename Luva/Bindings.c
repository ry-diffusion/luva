#include <lean/lean.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define Function LEAN_EXPORT lean_object *
static lean_external_class *gLoopClass = NULL;
static lean_external_class *gFileSystemRequestClass = NULL;

inline static void noop_foreach(void *mod, b_lean_obj_arg fn)
{
}

static void finalizeLoop(void *pLoop)
{
        assert(pLoop);

        uv_loop_close((uv_loop_t *)pLoop);
        free(pLoop);
}

static void finalizeFsRequest(void *pReq)
{
        uv_fs_req_cleanup((uv_fs_t *)pReq);
        free(pReq);
}

LEAN_EXPORT lean_obj_res luvaInitializeNative()
{
        gLoopClass = lean_register_external_class(finalizeLoop, noop_foreach);
        gFileSystemRequestClass =
            lean_register_external_class(finalizeFsRequest, noop_foreach);

        return lean_io_result_mk_ok(lean_box(0));
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

Function luvaTestCls(lean_object *obj)
{
        printf("is closure? %d\n", lean_is_closure(obj));
        // lean_object *(realFunction)(lean_object *);
        void *pFun = lean_closure_fun(obj);
        lean_object *R =
            ((lean_object * (*)(lean_object *)) pFun)(lean_box_uint32(4));

        return lean_io_result_mk_ok(R);
}

Function luvaMakeRequest()
{
        uv_fs_t *request = malloc(sizeof(uv_fs_t));
        memset(request, 0, sizeof(uv_fs_t));

        return lean_io_result_mk_ok(
            lean_alloc_external(gFileSystemRequestClass, request));
}

Function luvaCreateBuffer(lean_object *oSize)
{
        size_t size = lean_unbox_uint64(oSize);
        lean_object *array = lean_alloc_array(0, size);
}