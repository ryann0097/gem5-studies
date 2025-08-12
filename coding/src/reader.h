#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include "config.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>

class ConfigReader {
public:
    static Config parse_config_block(const std::string& block);
    static std::vector<Config> parse_all_configs(const std::string& full_text);
    static std::vector<Config> read(const std::string& filename);
};

#endif
