#ifndef HTML_H
#define HTML_H

#include <microhttpd.h>

char *render_page(const char *template_name);
enum MHD_Result send_html(struct MHD_Connection *connection, const char *html,
                          unsigned int status_code);

#endif
