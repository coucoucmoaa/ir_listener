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
#include <vector>


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
        bool ExtractMap(const std::string& filename);
        void showConfig(std::vector<std::string> &logs) const;
        ~Config();
        void pressKey(const std::vector<std::string>& keys);
        void openSite(const std::string& url);
        void addMapping(const std::string& irCode, const std::string& action);

        
    protected:
    private:
        std::unordered_map<std::string, std::string> _irToAction;
        std::string _name;
        Action _action;
        
};

#endif /* !CONFIG_HPP_ */
