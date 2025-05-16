cron-sendmail-default-recipient
===============================

Simple sendmail wrapper that replaces local cron email recipient.

This package replaces /usr/sbin/sendmail with wrapper that calls (diverted)
original version of /usr/sbin/sendmail, but it replaces last argument with
contents of /etc/cron-sendmail-default-recipient when called with -FCronDaemon
and last argument does not contain '@'.

Compatibility
=============

Tested on vixie cron on Debian 6 (Squeeze) to Debian 12 (Bookworm)
