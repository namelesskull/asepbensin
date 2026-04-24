#include "handlers.h"
#include <microhttpd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

static volatile sig_atomic_t running = 1;

static void handle_signal(int sig) {
    (void)sig;
    running = 0;
}

typedef enum MHD_Result (*handler_fn)(struct MHD_Connection *);

typedef enum {
    ROUTE_PAGE,
    ROUTE_FRAGMENT,
    ROUTE_STATIC,
} route_type;

typedef struct {
    const char *url;
    route_type type;
    const char *arg;
    const char *mime;
} route;

static const route routes[] = {
    {"/",             ROUTE_PAGE,     "home",    NULL},
    {"/about",        ROUTE_PAGE,     "about",   NULL},
    {"/contact",      ROUTE_PAGE,     "contact", NULL},
    {"/home-frag",    ROUTE_FRAGMENT, "home",    NULL},
    {"/about-frag",   ROUTE_FRAGMENT, "about",   NULL},
    {"/contact-frag", ROUTE_FRAGMENT, "contact", NULL},
    {"/js/htmx.min.js", ROUTE_STATIC, "assets/htmx.min.js", "application/javascript"},
};

static const size_t route_count = sizeof(routes) / sizeof(routes[0]);

static enum MHD_Result dispatch(const route *r,
                                struct MHD_Connection *connection) {
    switch (r->type) {
    case ROUTE_PAGE:
        return handle_page(connection, r->arg);
    case ROUTE_FRAGMENT:
        return handle_fragment(connection, r->arg);
    case ROUTE_STATIC:
        return handle_static(connection, r->arg, r->mime);
    }
    return handle_404(connection);
}

static enum MHD_Result router(void *cls, struct MHD_Connection *connection,
                              const char *url, const char *method,
                              const char *version, const char *upload_data,
                              size_t *upload_data_size, void **con_cls) {
    (void)cls;
    (void)method;
    (void)version;
    (void)upload_data;
    (void)upload_data_size;
    (void)con_cls;

    for (size_t i = 0; i < route_count; i++) {
        if (strcmp(url, routes[i].url) == 0)
            return dispatch(&routes[i], connection);
    }

    return handle_404(connection);
}

int main(void) {
    struct MHD_Daemon *server = MHD_start_daemon(
        MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, &router, NULL,
        MHD_OPTION_END);

    if (!server) {
        fprintf(stderr, "failed to start server on port %d\n", PORT);
        return 1;
    }

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf(":%d\n", PORT);

    while (running)
        pause();

    printf("\nshutting down\n");
    MHD_stop_daemon(server);
    return 0;
}
