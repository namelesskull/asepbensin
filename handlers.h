#ifndef HANDLERS_H
#define HANDLERS_H

#include <microhttpd.h>

enum MHD_Result handle_page(struct MHD_Connection *connection,
                            const char *template_name);
enum MHD_Result handle_fragment(struct MHD_Connection *connection,
                                const char *template_name);
enum MHD_Result handle_static(struct MHD_Connection *connection,
                              const char *path, const char *mime);
enum MHD_Result handle_404(struct MHD_Connection *connection);

#endif
