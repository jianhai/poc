/**
 *
 */
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched/task.h>
#include <linux/sched/task_stack.h>
#include <linux/sched/cputime.h>

#include <asm/processor.h>

static struct proc_dir_entry *eip_entry = NULL;

static int eip_show(struct seq_file *m, void *v)
{
	unsigned long gid, pid;
	unsigned long eip=0, esp=0;
	struct task_struct *task = current;

	while_each_thread(current, task) {

		if (task == current)
			continue;

		gid = task_tgid_nr(task);
		pid = task_pid_vnr(task);

		eip = KSTK_EIP(task);
		esp = task_pt_regs(task)->sp;

		seq_printf(m, "GID:%lu\tPID:%lu\tEIP:0x%08x\tESP:0x%08x\n", gid, pid, eip, esp);
	};
	
	return 0;
}

static int __init eip_init(void)
{
	eip_entry = proc_create_single("eip", 0, NULL, eip_show);

	return 0;
}

static void __exit eip_exit(void)
{
	if (eip_entry)
		proc_remove(eip_entry);

	eip_entry = NULL;
}

module_init(eip_init);
module_exit(eip_exit);

MODULE_AUTHOR("Jason Luan<luanjianhai@gmail.com>");
MODULE_LICENSE("GPL");
