#include "handlers.h"
#include "file_utils.h"
#include "html.h"
#include <stdlib.h>
#include <string.h>

enum MHD_Result handle_404(struct MHD_Connection *connection) {
  char *html = render_page("404");

  struct MHD_Response *response = MHD_create_response_from_buffer(
      strlen(html), (void *)html, MHD_RESPMEM_MUST_FREE);

  enum MHD_Result ret =
      MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
  MHD_destroy_response(response);

  return ret;
}

enum MHD_Result handle_home(struct MHD_Connection *connection) {
  char *html = render_page("home");

  send_html(connection, html);
  free(html);
  return MHD_YES;
}

enum MHD_Result handle_about(struct MHD_Connection *connection) {
  char *html = render_page("about");
  send_html(connection, html);
  free(html);
  return MHD_YES;
}

enum MHD_Result handle_contact(struct MHD_Connection *connection) {
  char *html = render_page("contact");
  send_html(connection, html);
  free(html);
  return MHD_YES;
}

enum MHD_Result handle_home_frag(struct MHD_Connection *connection) {
  char *html = read_file_to_string("templates/home.html");

  send_html(connection, html);
  free(html);
  return MHD_YES;
}

enum MHD_Result handle_about_frag(struct MHD_Connection *connection) {
  char *html = read_file_to_string("templates/about.html");

  send_html(connection, html);
  free(html);
  return MHD_YES;
}

enum MHD_Result handle_contact_frag(struct MHD_Connection *connection) {
  char *html = read_file_to_string("templates/contact.html");

  send_html(connection, html);
  free(html);
  return MHD_YES;
}
