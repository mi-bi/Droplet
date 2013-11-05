#ifndef __TOYSERVER_H__
#define __TOYSERVER_H__ 1

struct server_config
{
#if 0
    int sasl_plain;
    int sasl_login;
    int sasl_digestmd5;
    int starttls;
    int deflate;
    int caps_one_per_line;
#endif
};

struct connection
{
    int is_connected;
    int is_authenticated;
    int is_tls;
    int is_persistent;
#if 0
    SSL *tls_conn;
#endif
    FILE *in;
    FILE *out;
};

enum http_versions { V_1_0, V_1_1 };
enum http_methods { M_OPTIONS, M_GET, M_HEAD, M_POST, M_PUT, M_DELETE, M_TRACE, M_CONNECT };

struct request
{
    enum http_versions version;
    enum http_methods method;
    char uri[1024];
    char host[1024];
    struct kv *headers;
    int body_len;
    char body[4096];
};

struct reply
{
    int status;
    struct kv *headers;
    int body_len;
    char body[4096];
};

struct server_state
{
    /* dynamic configuration */
    struct server_config config;

    /* global state */
    pid_t pid;
    int rend_sock;
    int port;
    char url[256];

    /* per-connection state */
    struct connection connection;

    /* per-request state */
    struct request request;

    /* reply state */
    struct reply reply;
};

#endif /* __TOYSERVER_H__ */
