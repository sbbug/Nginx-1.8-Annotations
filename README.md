# Nginx-1.8-Annotations

## Nginx源码目录
   
    ├─auto 自动编译安装相关目录
    │ ├─cc 针对各种编译器进行相应的编译配置目录，包括Gcc、Ccc等
    │ ├─lib 程序依赖的各种库，包括md5,openssl,pcre等
    │ ├─os 针对不同操作系统所做的编译配置目录
    │ └─types
    ├─conf 相关配置文件等目录，包括nginx的配置文件、fcgi相关的配置等
    ├─contrib
    └─src 源码目录
        ├─core 核心源码目录，包括定义常用数据结构、体系结构实现等
        ├─event 封装的事件系统源码目录
        ├─http http服务器实现目录
        ├─mail 邮件代码服务器实现目录
        ├─misc 该目录当前版本只包含google perftools包
        └─os nginx对各操作系统下的函数进行封装以及实现核心调用的目录。
        └─stream nginx新增的模块，用来实现四层协议的转发、代理或者负载均衡。


