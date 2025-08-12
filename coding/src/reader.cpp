#include "reader.h"

#include <sstream>
#include <algorithm>

static int parse_size(const std::string& str) {
    return std::stoi(str); // você pode adaptar se quiser sufixos como "KB", "MB"
}

Config ConfigReader::parse_config_block(const std::string& block) {
    Config config;
    std::istringstream stream(block);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.find(":") == std::string::npos)
            continue;
            
        std::string key, value;
        std::istringstream linestream(line);
        std::getline(linestream, key, ':');
        std::getline(linestream, value);
        key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
        value.erase(0, value.find_first_not_of(" \t"));

        int val = 0;
        try{ val = std::stoi(value); } 
        catch (const std::invalid_argument& e){ continue; }


        if (key == "cpu-issue") config.set_cpu_issue(val);
        else if (key == "cpu-iq-entries") config.set_cpu_iq_entries(val);
        else if (key == "cpu-lq-entries") config.set_cpu_lq_entries(val);
        else if (key == "cpu-sq-entries") config.set_cpu_sq_entries(val);
        else if (key == "cpu-rob-entries") config.set_cpu_rob_entries(val);
        else if (key == "cpu-phy-intreg") config.set_cpu_phy_intreg(val);
        else if (key == "cpu-phy-floatreg") config.set_cpu_phy_floatreg(val);
        else if (key == "dcache-size") config.set_dcache_size(value + "kB");
        else if (key == "icache-size") config.set_icache_size(value + "kB");
        else if (key == "l2cache-size") config.set_l2cache_size(value + "kB");
        else if (key == "l3cache-size") config.set_l3cache_size(value + "kB");
        else if (key == "dcache-latency") config.set_dcache_latency(val);
    }
    return config;
}

std::vector<Config> ConfigReader::parse_all_configs(const std::string& full_text) {
    std::vector<Config> configs;
    std::istringstream input(full_text);
    std::string line, block;

    while (std::getline(input, line)) {
        if (line.find("Config") != std::string::npos && !block.empty()) {
            configs.push_back(parse_config_block(block));
            block.clear();
        }
        block += line + "\n";
    }

    if (!block.empty()){ configs.push_back(parse_config_block(block)); }

    return configs;
}

std::vector<Config> ConfigReader::read(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Falha durante a abertura do arquivo de configuração de nome: " + filename);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return parse_all_configs(buffer.str());
}
