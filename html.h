#ifndef HTML_H
#define HTML_H

#include <microhttpd.h>

void send_html(struct MHD_Connection *connection, const char *html);
char *render_page(const char *template_name);

#endif
