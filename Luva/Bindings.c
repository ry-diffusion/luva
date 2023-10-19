#include <lean/lean.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <uv/unix.h>

#define Function LEAN_EXPORT lean_object *
static lean_external_class *gLoopClass = NULL, *gFileSystemRequestClass = NULL,
                           *gBufferClass = NULL;

typedef lean_obj_res (*FSContinue)(lean_obj_arg);
inline static void noop_foreach(void *mod, b_lean_obj_arg fn)
{
}

static uv_buf_t *createSizedUvBuffer(size_t size)
{
        char *contents = calloc(size, sizeof(char));

        uv_buf_t *buf = malloc(sizeof(uv_buf_t));

        buf->base = contents;
        buf->len = size;

        return buf;
}

static void finalizeLoop(void *pLoop)
{
        assert(pLoop);

        uv_loop_close((uv_loop_t *)pLoop);
        free(pLoop);
}

static void finalizeBuffer(void *pBuffer)
{
        assert(pBuffer);
        uv_buf_t buffer = *(uv_buf_t *)pBuffer;

        free(buffer.base);
        free(pBuffer);
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
        gBufferClass =
            lean_register_external_class(finalizeBuffer, noop_foreach);

        return lean_io_result_mk_ok(lean_box(0));
}

Function luvaCreateLoop()
{
        uv_loop_t *loop = (uv_loop_t *)malloc(sizeof(uv_loop_t));
        assert(loop);

        uv_loop_init(loop);
        return lean_io_result_mk_ok(lean_alloc_external(gLoopClass, loop));
}

Function luvaRunLoop(lean_object *obj, lean_object *obj2)
{
        uv_loop_t *L = lean_get_external_data(obj);
        unsigned int runMode = lean_unbox_uint32(obj2);

        return lean_io_result_mk_ok(
            lean_box_uint32(uv_run(L, (uv_run_mode)runMode)));
}

static void fsCallbackProcess(uv_fs_t *req)
{
        assert(lean_is_closure(req->data));

        lean_object *monad = ((FSContinue)(lean_closure_fun(req->data)))(
            lean_alloc_external(gFileSystemRequestClass, req));

        (void)monad;
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
        uv_fs_t *request = (uv_fs_t *)malloc(sizeof(uv_fs_t));
        memset(request, 0, sizeof(uv_fs_t));

        return lean_io_result_mk_ok(
            lean_alloc_external(gFileSystemRequestClass, request));
}

Function luvaOpenFile(lean_obj_arg self, lean_obj_arg objPath,
                      lean_obj_arg objRequest, lean_obj_arg objFlags,
                      lean_obj_arg objMode, lean_obj_arg objNext)
{
        uv_loop_t *L = lean_get_external_data(self);
        uv_fs_t *req = lean_get_external_data(objRequest);
        const char *path = lean_string_cstr(objPath);
        const uint32_t flags = lean_unbox_uint32(objFlags);
        const uint32_t mode = lean_unbox_uint32(objMode);
        req->data = objNext;
        if (uv_fs_open(L, req, path, flags, mode, fsCallbackProcess) != 0)
        {
                return lean_io_result_mk_error(lean_mk_io_user_error(
                    lean_mk_string("unable to open file")));
        }

        return lean_io_result_mk_ok(lean_box(0));
}

Function luvaCreateBuffer(lean_object *objSize)
{
        size_t size = lean_unbox(objSize) << 1;
        uv_buf_t *buf = createSizedUvBuffer(size);

        return lean_io_result_mk_ok(lean_alloc_external(gBufferClass, buf));
}

Function luvaBufferAsArray(lean_object *objSelf)
{
        uv_buf_t *buff = lean_get_external_data(objSelf);
        lean_obj_res leanArray = lean_mk_empty_byte_array(lean_box(buff->len));

        for (size_t idx = 0; idx < buff->len; ++idx)
                lean_byte_array_push(leanArray, buff->base[idx]);

        return lean_io_result_mk_ok(leanArray);
}

Function luvaBufferFromByteArray(lean_object *objSelf)
{
        lean_obj_res byteArray = lean_copy_byte_array(objSelf);
        size_t bufferSize = lean_unbox(lean_byte_array_size(byteArray));
        uv_buf_t *ioBuffer = createSizedUvBuffer(bufferSize);

        for (size_t idx = 0; idx < bufferSize; ++idx)
                ioBuffer->base[idx] =
                    lean_byte_array_get(byteArray, lean_box(idx));

        return lean_io_result_mk_ok(
            lean_alloc_external(gBufferClass, ioBuffer));
}

Function luvaRequestResult(lean_object *objSelf)
{
        uv_fs_t *req = lean_get_external_data(objSelf);
        return lean_io_result_mk_ok(lean_box(req->result));
}