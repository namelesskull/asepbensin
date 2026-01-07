#include "handlers.h"
#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *load_file(const char *path, size_t *out_len) {
  FILE *f = fopen(path, "rb");
  if (!f)
    return NULL;

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buf = malloc(size);
  if (!buf) {
    fclose(f);
    return NULL;
  }

  fread(buf, 1, size, f);
  fclose(f);

  *out_len = size;
  return buf;
}

enum MHD_Result handle_htmx(struct MHD_Connection *connection) {
  size_t len;
  char *buf = load_file("./assets/htmx.min.js", &len);
  if (!buf)
    return handle_404(connection);

  struct MHD_Response *response =
      MHD_create_response_from_buffer(len, (void *)buf, MHD_RESPMEM_MUST_FREE);

  MHD_add_response_header(response, "Content-Type", "application/javascript");

  enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}

enum MHD_Result handle_font(struct MHD_Connection *connection) {
  size_t len;
  char *buf = load_file("./assets/htmx.min.js", &len);
  if (!buf)
    return handle_404(connection);

  struct MHD_Response *response =
      MHD_create_response_from_buffer(len, (void *)buf, MHD_RESPMEM_MUST_FREE);

  MHD_add_response_header(response, "Content-Type", "application/javascript");

  enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}

enum MHD_Result router(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method, const char *version,
                       const char *upload_data, size_t *upload_data_size,
                       void **con_cls) {
  (void)cls;
  (void)method;
  (void)version;
  (void)upload_data;
  (void)upload_data_size;
  (void)con_cls;

  if (strcmp(url, "/") == 0)
    return handle_home(connection);
  if (strcmp(url, "/about") == 0)
    return handle_about(connection);
  if (strcmp(url, "/contact") == 0)
    return handle_contact(connection);
  if (strcmp(url, "/home-frag") == 0)
    return handle_home_frag(connection);
  if (strcmp(url, "/about-frag") == 0)
    return handle_about_frag(connection);
  if (strcmp(url, "/contact-frag") == 0)
    return handle_contact_frag(connection);

  if (strcmp(url, "/js/htmx.min.js") == 0)
    return handle_htmx(connection);

  return handle_404(connection);
}

int main() {
  int port = 8080;
  struct MHD_Daemon *server =
      MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, port, NULL, NULL,
                       &router, NULL, MHD_OPTION_END);

  if (!server)
    return 1;

  printf(":%d\n", port);
  getchar();
  MHD_stop_daemon(server);
  return 0;
}
