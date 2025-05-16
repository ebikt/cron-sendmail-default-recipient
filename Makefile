PREFIX  = /usr
SBINDIR = $(PREFIX)/sbin

all: cron-sendmail-default-recipient

cron-sendmail-default-recipient: wrapper.c
	gcc $(CFLAGS) $(LDFLAGS) -DSBINDIR='$(SBINDIR)' -Wall $^ -o $@

install: cron-sendmail-default-recipient
	install -m 755 -d $(DESTDIR)$(SBINDIR)/
	install -m 755 -t $(DESTDIR)$(SBINDIR)/ cron-sendmail-default-recipient
	if [ ! -e $(DESTDIR)$(SBINDIR)/cron-sendmail-default-original ] && \
	   find $(DESTDIR)$(SBINDIR)/sendmail -not -lname cron-sendmail-default-recipient | grep -q . ;\
	then \
		mv $(DESTDIR)$(SBINDIR)/sendmail \
		   $(DESTDIR)$(SBINDIR)/cron-sendmail-default-original; \
	fi
	ln -s cron-sendmail-default-recipient $(DESTDIR)$(SBINDIR)/sendmail

clean:
	rm -f cron-sendmail-default-recipient
