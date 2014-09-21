#ifndef _LINUX_CEC_DEV_H
#define _LINUX_CEC_DEV_H

#include <linux/cdev.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/sched.h>

#include <uapi/linux/cec-dev.h>

enum {
	CEC_DEV_WRITE_AVAIL = 0,
	CEC_DEV_WRITE_BUSY,
	CEC_DEV_WRITE_OK,
	CEC_DEV_WRITE_KO
};

struct device;

struct cec_dev {
	struct cdev cdev;
	dev_t devn;

	struct mutex mutex;
	unsigned users;

	spinlock_t lock;
	wait_queue_head_t waitq;
	struct list_head events;
	u8 write_state;

	//u8 retries;
	u16 addresses;
	u16 physical;

	int (*open)(struct cec_dev *);
	void (*release)(struct cec_dev *);
	void (*send_message)(struct cec_dev *, u8 *, size_t);
	void (*set_address)(struct cec_dev *, unsigned);
};

void cec_dev_event(struct cec_dev *cec_dev, int type, u8 *msg, size_t len);

static inline void cec_dev_receive(struct cec_dev *cec_dev, u8 *msg,
	unsigned len)
{
	cec_dev_event(cec_dev, MESSAGE_TYPE_RECEIVE_SUCCESS, msg, len);
}

static inline void cec_dev_send_complete(struct cec_dev *cec_dev, int ack)
{
	// Paranoid guard - Should always be true unless undefined hw behavior
	if (cec_dev->write_state == CEC_DEV_WRITE_BUSY)
		cec_dev->write_state = ack ? CEC_DEV_WRITE_OK : CEC_DEV_WRITE_KO ;
	wake_up(&cec_dev->waitq);
}

static inline void cec_dev_disconnect(struct cec_dev *cec_dev)
{
	cec_dev->physical = 0;
	cec_dev_event(cec_dev, MESSAGE_TYPE_DISCONNECTED, NULL, 0);
}

static inline void cec_dev_connect(struct cec_dev *cec_dev, u32 phys)
{
	cec_dev->physical = phys;
	cec_dev_event(cec_dev, MESSAGE_TYPE_CONNECTED, NULL, 0);
}

void cec_dev_init(struct cec_dev *cec_dev, struct module *);
int cec_dev_add(struct cec_dev *cec_dev, struct device *, const char *name);
void cec_dev_remove(struct cec_dev *cec_dev);

#endif
