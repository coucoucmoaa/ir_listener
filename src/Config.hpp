/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Config
*/

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <unordered_map>
#include <string>

enum class Action {
    NONE,
    STOP,
    MOUSELEFTC,
    MOUSERIGHTC,
    CTRLW,
    CTRLT,
    YOUTUBE,
    TWITCH,
    NETFLIX,
    DISCORD,
    ANIME,
    VOLUMEUP,
    VOLUMEDOWN,
    VOLUMEMUTE,
    PAUSE,
    FULLSCREEN,
    TOGGLE
};

class Config {
    public:
        Config(const std::string& name);
        void listenAndMap(const std::string &irCode);
        void saveToJson(const std::string& filename) const;
        const std::unordered_map<std::string, std::string>& getMap() const;
        void ExtractMap(const std::string& filename);
        void showConfig();
        ~Config();

        
    protected:
    private:
        std::unordered_map<std::string, std::string> _irToAction;
        std::string _name;
        Action _action;
};

#endif /* !CONFIG_HPP_ */
