#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <sstream>

class Config {
private:
	std::string current_mode;
	int cpu_issue, cpu_iq_entries, cpu_lq_entries, cpu_sq_entries;
	int cpu_rob_entries, cpu_phy_intreg, cpu_phy_floatreg;
	std::string dcache_size, icache_size, l2cache_size, l3cache_size;
	int dcache_latency;

public:
	Config(){}

	//==[ Setters ]
	void set_cpu_issue(int value);
	void set_cpu_iq_entries(int value);
	void set_cpu_lq_entries(int value);
	void set_cpu_sq_entries(int value);
	void set_cpu_rob_entries(int value);
	void set_cpu_phy_intreg(int value);
	void set_cpu_phy_floatreg(int value);
	void set_dcache_size(std::string value);
	void set_icache_size(std::string value);
	void set_l2cache_size(std::string value);
	void set_l3cache_size(std::string value);
	void set_dcache_latency(int value);

	//==[ Getters ]
	int get_cpu_issue();
	int get_cpu_iq_entries();
	int get_cpu_lq_entries();
	int get_cpu_sq_entries();
	int get_cpu_rob_entries();
	int get_cpu_phy_intreg();
	int get_cpu_phy_floatreg();
	std::string get_dcache_size();
	std::string get_icache_size();
	std::string get_l2cache_size();
	std::string get_l3cache_size();
	int get_dcache_latency();
	
	std::string config_to_args();
	
	void load_mode();

	~Config(){}
};

#endif
