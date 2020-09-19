
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>

//基于参数创建一个数组
ngx_array_t *
ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size)
{
    ngx_array_t *a;

    a = ngx_palloc(p, sizeof(ngx_array_t));//从内存池中分配内存
    if (a == NULL) {
        return NULL;
    }

    if (ngx_array_init(a, p, n, size) != NGX_OK) {//初始化分配好的数组
        return NULL;
    }

    return a;
}

//销毁数组
void
ngx_array_destroy(ngx_array_t *a)
{
    ngx_pool_t  *p;

    p = a->pool;

    if ((u_char *) a->elts + a->size * a->nalloc == p->d.last) {
        p->d.last -= a->size * a->nalloc;//更新内存池的偏移量，其实是逻辑销毁
    }

    if ((u_char *) a + sizeof(ngx_array_t) == p->d.last) {
        p->d.last = (u_char *) a;
    }
}

//添加单个元素到数组，
void *
ngx_array_push(ngx_array_t *a)
{
    void        *elt, *new;
    size_t       size;
    ngx_pool_t  *p;

    if (a->nelts == a->nalloc) {//数组满了：当前容量等于最大值

        /* the array is full */

        size = a->size * a->nalloc;//当前数组占用多少个字节的内存

        p = a->pool;

        if ((u_char *) a->elts + size == p->d.last
            && p->d.last + a->size <= p->d.end)// 该数组位于内存池末尾，并且末尾的快有足够容量
        {
            /*
             * the array allocation is the last in the pool
             * and there is space for new allocation
             */
            //修改内存池末尾指针位置，指向下一个空的块
            p->d.last += a->size;
            a->nalloc++;//容量个数++

        } else {
            /* allocate a new array */
            //内存不够，动态扩容
            new = ngx_palloc(p, 2 * size);//从内存池中申请2倍的内存
            if (new == NULL) {
                return NULL;
            }

            ngx_memcpy(new, a->elts, size);//将数据copy到新的内存
            a->elts = new;//更新数组中的数据指针
            a->nalloc *= 2;//容量*2
        }
    }

    elt = (u_char *) a->elts + a->size * a->nelts;//数据指针偏移到当前元素位置
    a->nelts++;//数组当前个数+1

    return elt;
}

//添加n个元素到数组中
void *
ngx_array_push_n(ngx_array_t *a, ngx_uint_t n)
{
    void        *elt, *new;
    size_t       size;
    ngx_uint_t   nalloc;
    ngx_pool_t  *p;

    size = n * a->size;//n个元素所占内存

    if (a->nelts + n > a->nalloc) {//容量不够，进行扩容

        /* the array is full */

        p = a->pool;

        if ((u_char *) a->elts + a->size * a->nalloc == p->d.last
            && p->d.last + size <= p->d.end)
        {
            /*
             * the array allocation is the last in the pool
             * and there is space for new allocation
             */

            p->d.last += size;
            a->nalloc += n;

        } else {
            /* allocate a new array */

            nalloc = 2 * ((n >= a->nalloc) ? n : a->nalloc);

            new = ngx_palloc(p, nalloc * a->size);
            if (new == NULL) {
                return NULL;
            }

            ngx_memcpy(new, a->elts, a->nelts * a->size);
            a->elts = new;
            a->nalloc = nalloc;
        }
    }

    elt = (u_char *) a->elts + a->size * a->nelts;
    a->nelts += n;

    return elt;
}
