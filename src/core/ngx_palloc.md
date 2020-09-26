
## nginx内存池技术
    
    // ngx_pool_t是ngx_pool_s的别名
    typedef struct ngx_pool_s    ngx_pool_t;
    
    ngx_pool_t  *p;//创建一个指针
    p = ngx_memalign(NGX_POOL_ALIGNMENT, size, log);//分配堆内存
    if (p == NULL) {
        return NULL;
    }
    //
    #if (NGX_HAVE_POSIX_MEMALIGN || NGX_HAVE_MEMALIGN)
    void *ngx_memalign(size_t alignment, size_t size, ngx_log_t *log);
    #else
    #define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)
    #endif
    //堆内存分配函数
    void *
    ngx_alloc(size_t size, ngx_log_t *log)
    {
        void  *p;
    
        p = malloc(size);//分配内存大小
        if (p == NULL) {
            ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                          "malloc(%uz) failed", size);
        }
    
        ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, log, 0, "malloc: %p:%uz", p, size);
    
        return p;
    }