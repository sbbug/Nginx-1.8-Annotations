

## nginx数组结构

#### 数组内部属性结构

      typedef struct {
            void        *elts;//指向数据的指针
            ngx_uint_t   nelts;//当前数组元素数量
            size_t       size;//元素大小
            ngx_uint_t   nalloc;//数组容量
            ngx_pool_t  *pool;//内存池句柄
     } ngx_array_t;
     //原来每个数组内部会有一个内存池句柄，专门用来给数组扩容用的，Nginx妙不可言！！
     
    
    // ngx_uint_t ngx_pool_t 位于ngx_config.h中定义
        typedef intptr_t        ngx_int_t;
        typedef uintptr_t       ngx_uint_t;
    // intptr_t uintptr_t位于Linux内核文件/usr/include/stdint.h中
    大致如下
        /* Types for `void *' pointers.  */
        #if __WORDSIZE == 64
        # ifndef __intptr_t_defined
        typedef long int		intptr_t;
        #  define __intptr_t_defined
        # endif
        typedef unsigned long int	uintptr_t;
        #else
        # ifndef __intptr_t_defined
        typedef int			intptr_t;
        #  define __intptr_t_defined
        # endif
        typedef unsigned int		uintptr_t;
        #endif
    //ngx_pool_t
    位于ngx_core.h下
    typedef struct ngx_pool_s            ngx_pool_t;
    //ngx_pool_s 位于ngx_core.h下面
        struct ngx_pool_s {
            ngx_pool_data_t       d;
            size_t                max;
            ngx_pool_t           *current;
            ngx_chain_t          *chain;
            ngx_pool_large_t     *large;
            ngx_pool_cleanup_t   *cleanup;
            ngx_log_t            *log;
        };

#### note

    #define ngx_inline      inline //内联关键字别名
    inline可以修饰方法和变量
    
#### 
#### [转 ngx_palloc 内存池](./ngx_palloc.md)