#include <libconfig.h>
#include "config.h"

config_t cfg;

int opts_init() {
  config_init(&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "pinex.cfg"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return 0;
  }
  return 1;
}
int opts_save() {
  /* Write out the new configuration. */
  if(! config_write_file(&cfg, "pinex.cfg"))
  {
    fprintf(stderr, "Error while writing file.\n");
    config_destroy(&cfg);
    return 0;
  }
  fprintf(stderr, "New configuration successfully written to: pinex.cfg\n");
  return 1;
}

int opts_final() {
	config_destroy(&cfg);
	return 1;
}

int opts_connection_timeout() {
	int timeout = 12;
	config_lookup_int(&cfg, "client.timeout", &timeout);
	return timeout;
}

int opts_mx_port() {
	int port = 25;
	config_lookup_int(&cfg, "client.port", &port);
	return port;
}

const char *opts_my_domain() {
	const char *my_domain = "quint.com";
	config_lookup_string(&cfg, "client.domain", &my_domain);
	return my_domain;
}

const char *opts_maildir_root() {
	const char *root = "../maildir";
	config_lookup_string(&cfg, "client.maildir", &root);
	return root;
}

const char *opts_read(const char * addr) {
	const char *output;
	config_lookup_string(&cfg, addr, &output);
	return output;
}

const char *opts_appname() {
	const char *appname;
	config_lookup_string(&cfg, "pinex.app.AppName", &appname);
	return appname;
}

const char *opts_version() {
	const char *version;
	config_lookup_string(&cfg, "pinex.app.Version", &version);
	return version;
}

const char *opts_desc() {
	const char *desc;
	config_lookup_string(&cfg, "pinex.app.Desc", &desc);
	return desc;
}