#include "handlers.h"
#include "file_utils.h"
#include "html.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum MHD_Result handle_page(struct MHD_Connection *connection,
                            const char *template_name) {
    char *html = render_page(template_name);
    enum MHD_Result ret = send_html(connection, html, MHD_HTTP_OK);
    free(html);
    return ret;
}

enum MHD_Result handle_fragment(struct MHD_Connection *connection,
                                const char *template_name) {
    char path[256];
    snprintf(path, sizeof(path), "templates/%s.html", template_name);

    char *html = read_file_str(path);
    enum MHD_Result ret = send_html(connection, html, MHD_HTTP_OK);
    free(html);
    return ret;
}

enum MHD_Result handle_static(struct MHD_Connection *connection,
                              const char *path, const char *mime) {
    size_t len;
    char *buf = read_file(path, &len);
    if (!buf)
        return handle_404(connection);

    struct MHD_Response *response =
        MHD_create_response_from_buffer(len, buf, MHD_RESPMEM_MUST_FREE);

    if (!response) {
        free(buf);
        return MHD_NO;
    }

    MHD_add_response_header(response, "Content-Type", mime);
    enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

enum MHD_Result handle_404(struct MHD_Connection *connection) {
    char *html = render_page("404");
    enum MHD_Result ret = send_html(connection, html, MHD_HTTP_NOT_FOUND);
    free(html);
    return ret;
}
