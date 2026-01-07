
#ifndef HANDLERS_H
#define HANDLERS_H

#include <microhttpd.h>

enum MHD_Result handle_home(struct MHD_Connection *connection);
enum MHD_Result handle_about(struct MHD_Connection *connection);
enum MHD_Result handle_contact(struct MHD_Connection *connection);
enum MHD_Result handle_home_frag(struct MHD_Connection *connection);
enum MHD_Result handle_about_frag(struct MHD_Connection *connection);
enum MHD_Result handle_contact_frag(struct MHD_Connection *connection);
enum MHD_Result handle_404(struct MHD_Connection *connection);

#endif
