#include "html.h"
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LAYOUT_PATH "templates/layout.html"
#define BODY_TAG "{{body}}"
#define BODY_TAG_LEN 8

static void trim_trailing(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r' ||
                       s[len - 1] == ' '))
        s[--len] = '\0';
}

char *render_page(const char *template_name) {
    char path[256];
    snprintf(path, sizeof(path), "templates/%s.html", template_name);

    char *body = read_file_str(path);
    if (!body)
        return NULL;
    trim_trailing(body);

    char *layout = read_file_str(LAYOUT_PATH);
    if (!layout) {
        free(body);
        return NULL;
    }
    trim_trailing(layout);

    char *pos = strstr(layout, BODY_TAG);
    if (!pos) {
        free(body);
        return layout;
    }

    size_t before = (size_t)(pos - layout);
    size_t body_len = strlen(body);
    size_t after = strlen(layout) - before - BODY_TAG_LEN;
    size_t total = before + body_len + after + 1;

    char *html = malloc(total);
    if (!html) {
        free(body);
        free(layout);
        return NULL;
    }

    memcpy(html, layout, before);
    memcpy(html + before, body, body_len);
    memcpy(html + before + body_len, pos + BODY_TAG_LEN, after);
    html[total - 1] = '\0';

    free(body);
    free(layout);
    return html;
}

enum MHD_Result send_html(struct MHD_Connection *connection, const char *html,
                          unsigned int status_code) {
    if (!html) {
        html = "500 Internal Server Error";
        status_code = MHD_HTTP_INTERNAL_SERVER_ERROR;
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(
        strlen(html), (void *)html, MHD_RESPMEM_MUST_COPY);

    if (!response)
        return MHD_NO;

    MHD_add_response_header(response, "Content-Type", "text/html");
    enum MHD_Result ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
    return ret;
}
