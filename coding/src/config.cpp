#include "config.h"

//==[ Setters ]

void Config::set_cpu_issue(int value){ cpu_issue = value; }
void Config::set_cpu_iq_entries(int value){ cpu_iq_entries = value; }
void Config::set_cpu_lq_entries(int value){ cpu_lq_entries = value; }
void Config::set_cpu_sq_entries(int value){ cpu_sq_entries = value; }
void Config::set_cpu_rob_entries(int value){ cpu_rob_entries = value; }
void Config::set_cpu_phy_intreg(int value){ cpu_phy_intreg = value; }
void Config::set_cpu_phy_floatreg(int value){ cpu_phy_floatreg = value; }
void Config::set_dcache_size(std::string value){ dcache_size = value; }
void Config::set_icache_size(std::string value){ icache_size = value; }
void Config::set_l2cache_size(std::string value){ l2cache_size = value; }
void Config::set_l3cache_size(std::string value){ l3cache_size = value; }
void Config::set_dcache_latency(int value){ dcache_latency = value; }

//==[ Getters ]

int Config::get_cpu_issue(){ return cpu_issue; }
int Config::get_cpu_iq_entries(){ return cpu_iq_entries; }
int Config::get_cpu_lq_entries(){ return cpu_lq_entries; }
int Config::get_cpu_sq_entries(){ return cpu_sq_entries; }
int Config::get_cpu_rob_entries(){ return cpu_rob_entries; }
int Config::get_cpu_phy_intreg(){ return cpu_phy_intreg; }
int Config::get_cpu_phy_floatreg(){ return cpu_phy_floatreg; }
std::string Config::get_dcache_size(){ return dcache_size; }
std::string Config::get_icache_size(){ return icache_size; }
std::string Config::get_l2cache_size(){ return l2cache_size; }
std::string Config::get_l3cache_size(){ return l3cache_size; }
int Config::get_dcache_latency(){ return dcache_latency; }

std::string Config::config_to_args(){
    std::ostringstream cmd_str;
    cmd_str << " --cpu-iq-entries " << cpu_iq_entries
            << " --cpu-rob-entries " << cpu_rob_entries
            << " --cpu-lq-entries " << cpu_lq_entries
            << " --cpu-sq-entries " << cpu_sq_entries
            << " --cpu-fetch-width " << cpu_issue
            << " --cpu-issue-width " << cpu_issue
            << " --cpu-commit-width " << cpu_issue
            << " --cpu-smt-threads 2"
            << " --cpu-phys-int-regs " << cpu_phy_intreg
            << " --cpu-phys-float-regs " << cpu_phy_floatreg
            << " --l1d-size " << dcache_size
            << " --l1i-size " << icache_size
            << " --l2-size " << l2cache_size
            << " --l3-size " << l3cache_size
            << " --dcache-hit-latency " << dcache_latency;
    return cmd_str.str();
}

