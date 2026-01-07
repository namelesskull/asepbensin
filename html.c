#include "html.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *load_file(const char *path) {
  FILE *f = fopen(path, "rb");
  if (!f)
    return NULL;

  if (fseek(f, 0, SEEK_END) != 0) {
    fclose(f);
    return NULL;
  }

  long size = ftell(f);
  if (size < 0) {
    fclose(f);
    return NULL;
  }
  rewind(f);

  char *buffer = malloc(size + 1);
  if (!buffer) {
    fclose(f);
    return NULL;
  }

  size_t read = fread(buffer, 1, (size_t)size, f);
  if (read != (size_t)size) {
    free(buffer);
    fclose(f);
    return NULL;
  }

  buffer[size] = '\0';
  fclose(f);
  return buffer;
}

static void trim_trailing(char *s) {
  size_t len = strlen(s);
  while (len > 0 &&
         (s[len - 1] == '\n' || s[len - 1] == '\r' || s[len - 1] == ' ')) {
    s[len - 1] = '\0';
    len--;
  }
}

char *render_page(const char *template_name) {
  char template_path[256];
  snprintf(template_path, sizeof(template_path), "templates/%s.html",
           template_name);

  char *body = load_file(template_path);
  if (!body)
    return NULL;
  trim_trailing(body);

  char *layout = load_file("templates/layout.html");
  if (!layout) {
    free(body);
    return NULL;
  }
  trim_trailing(layout);

  char *pos = strstr(layout, "{{body}}");
  if (!pos) {
    free(body);
    return layout;
  }

  size_t layout_len = strlen(layout);
  size_t before_len = pos - layout;
  size_t after_len = layout_len - before_len - 8;

  size_t final_len = before_len + strlen(body) + after_len + 1;
  char *html = malloc(final_len);
  if (!html) {
    free(body);
    free(layout);
    return NULL;
  }

  memcpy(html, layout, before_len);
  memcpy(html + before_len, body, strlen(body));
  memcpy(html + before_len + strlen(body), pos + 8, after_len);
  html[final_len - 1] = '\0';

  free(body);
  free(layout);

  return html;
}

void send_html(struct MHD_Connection *connection, const char *html) {
  if (!html)
    html = "500 Internal Server Error";

  struct MHD_Response *response = MHD_create_response_from_buffer(
      strlen(html), (void *)html, MHD_RESPMEM_MUST_COPY);

  if (!response)
    return;

  MHD_add_response_header(response, "Content-Type", "text/html");
  MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);
}
