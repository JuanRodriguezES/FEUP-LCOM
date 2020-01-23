PROG=proj

SRCS = proj.c graphics_card.c Menu.c Player.c Enemy.c Level.c Game.c timer.c kbd.c mouse.c Button.c Bullet.c Door.c Lever.c rtc.c DateTime.c MultiPlayer.c serial_port.c queue.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
