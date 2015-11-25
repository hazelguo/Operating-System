#include <linux/init.h>
#include <linux/module.h>
#include <asm/msr.h>
MODULE_LICENSE("Proprietary");
struct CACHE_NODE
{
	long long i_qword[4];
	unsigned int i_tag_lru_v;
	long long d_qword[4];
	unsigned int d_tag_lru_v;
};
struct CACHE_NODE node[1 << 9];
static int __init dump_cache_MSR_init(void)
{
	printk("dump_cache_MSR: Hello, world!\n");
	unsigned int i_config;
	unsigned int i_index;
	unsigned int i_data;
	unsigned int i_tag_inc;
	i_config = 0x1700;
	i_index = 0x1710;
	i_data = 0x1711;
	i_tag_inc = 0x1713;
	int i;
	int low, high;
	long long tmp;
	
	rdmsr(i_config, low, high);
	low = (0xf << 12) | low;
	wrmsr(i_config, low, high);//lock L1 instruction cache
	
	for (i=0;i<(1<<9);i++)
	{
		rdmsr(i_index, low, high);
		low = high = 0;
		wrmsr(i_index, low, high);//初始化index
		
		rdmsr(i_data, low, high);
		tmp = high;
		node[i].i_qword[0] = low + (tmp << 32);
		rdmsr(i_data, low, high);
		tmp = high;
		node[i].i_qword[1] = low + (tmp << 32);
		rdmsr(i_data, low, high);
		tmp = high;
		node[i].i_qword[2] = low + (tmp << 32);
		rdmsr(i_data, low, high);
		tmp = high;
		node[i].i_qword[3] = low + (tmp << 32);
		
		rdmsr(i_tag_inc, low, high);//读Instruction Cache Read/Write Tag w/INC Register自动自增index register
		node[i].i_tag_lru_v = low;
	}
	rdmsr(i_config, low, high);
	low = (~(0xf << 12)) & low;
	wrmsr(i_config, low, high);//unlock L1 instruction cache
	
	unsigned int d_config;
	unsigned int d_index;
	unsigned int d_data;
	unsigned int d_tag_inc;
	d_config = 0x1800;
	d_index = 0x1890;
	d_data = 0x1891;
	d_tag_inc = 0x1893;
	
	rdmsr(d_config, low, high);
	low = (0xf << 16) | low;
	wrmsr(d_config, low, high);//lock L1 data cache
	
	for (i = 0; i < (1 << 9); i++)
	{
		rdmsr(d_index, low, high);
		low = high = 0;
		wrmsr(d_index, low, high);//初始化index
		
		rdmsr(d_data, low, high);
		tmp = high;
		node[i].d_qword[0] = low + (tmp << 32);
		rdmsr(d_data, low, high);
		tmp = high;
		node[i].d_qword[1] = low + (tmp << 32);
		rdmsr(d_data, low, high);
		tmp = high;
		node[i].d_qword[2] = low + (tmp << 32);
		rdmsr(d_data, low, high);
		tmp = high;
		node[i].d_qword[3] = low + (tmp << 32);
		
		rdmsr(d_tag_inc, low, high);
		node[i].d_tag_lru_v = low;
	}
	rdmsr(d_config, low, high);
	low = (~(0xf << 16)) & low;
	wrmsr(d_config, low, high);//unlock L1 data cache
	for (i = 0; i < (1 << 9); i++)
	{
		printk("instruction cache %d:\n",i);
		printk("QWORDs:%p %p %p %p\n", node[i].i_qword[0], node[i].i_qword[1], node[i].i_qword[2], node[i].i_qword[3]);
		printk("tag_lru_v: %p\n", node[i].i_tag_lru_v);
		printk("data cache %d:\n",i);
		printk("QWORDs:%p %p %p %p\n",
			node[i].d_qword[0],
			node[i].d_qword[1],
			node[i].d_qword[2],
			node[i].d_qword[3]);
		printk("tag_lru_v: %p\n", node[i].d_tag_lru_v);
	}
	return 0;
}

static void __exit dump_cache_MSR_exit(void)
{
	printk("dump_cache_MSR: Goodbye, world!\n");
}

module_init(dump_cache_MSR_init);
module_exit(dump_cache_MSR_exit);
