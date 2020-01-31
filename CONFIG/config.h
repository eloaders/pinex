#ifndef _CONFIG_H_
#define _CONFIG_H

int opts_init();
int opts_save();
int opts_final();

int opts_mx_port();
int opts_connection_timeout();
const char *opts_maildir_root();
const char *opts_my_domain();
const char *opts_read(const char * addr);
const char *opts_appname();
const char *opts_version();
const char *opts_desc();
#endif