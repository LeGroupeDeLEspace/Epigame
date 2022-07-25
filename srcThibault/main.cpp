#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

void writeInYamlFile()
{
    YAML::Emitter out;
    out << "Hello, World!";

    out << YAML::BeginSeq;
    out << "eggs";
    out << "bread";
    out << "milk";
    out << YAML::EndSeq;

    out << YAML::BeginMap;
    out << YAML::Key << "name";
    out << YAML::Value << "Ryan Braun";
    out << YAML::Key << "position";
    out << YAML::Value << "LF";
    out << YAML::EndMap;

    out << YAML::BeginMap;
    out << YAML::Key << "name";
    out << YAML::Value << "Barack Obama";
    out << YAML::Key << "children";
    out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;

    std::cout << "Here's the output YAML:\n" << out.c_str()  << std::endl; // prints "Hello, World!"
}

bool LoadFileAndPrint(std::string filename)
{
    YAML::Node config = YAML::LoadFile(filename);
    
    if (!config) {
        std::cout << "The file couldn't be loaded!\n";
        return false;
    }
    std::cout << "The content of our yaml file:\n" << config << std::endl;
    return true;
}

std::vector<std::string> returnWitchSwitch(const YAML::Node &tmp, std::vector<std::string> &vec)
{
    switch (tmp.Type())
    {
        case YAML::NodeType::Null :
            std::cout << "Null\n";
            break;
        case YAML::NodeType::Scalar :
            std::cout << "Scalar\n";
            break;
        case YAML::NodeType::Sequence :
            std::cout << "Sequence\n";
            for (YAML::const_iterator it = tmp.begin(); it != tmp.end(); it++) {
                std::string test = it->as<std::string>();
                vec.push_back(test);
            }
            return std::vector<std::string>();
        case YAML::NodeType::Map :
            std::cout << "Map\n";
            break;
        default :
            std::cout << "default\n";
    }
    return std::vector<std::string>();
}

std::vector<std::string> GetTheYamlValueRec(const YAML::Node &rec, std::vector<std::string> &vecStr, std::vector<std::string> &result)
{
    if (!rec)
        return std::vector<std::string>();
    const YAML::Node& tmp = rec[vecStr.at(0)];
    if (tmp) {
        if (vecStr.size() == 1) {
            returnWitchSwitch(tmp, result);
            return result;
        }
        vecStr.erase(vecStr.begin());
        GetTheYamlValueRec(tmp, vecStr, result);
    }
    return std::vector<std::string>();
}

std::vector<std::string> GetTheYamlValue(std::vector<std::string> &vecStr)
{
    YAML::Node config = YAML::LoadFile("./srcThibault/InputsConfig.yaml");
    std::vector<std::string> result;

    if (!config)
        std::cout << "The file couldn't be loaded!\n";
    if (vecStr.size() == 0)
        return std::vector<std::string>();
    const YAML::Node& rec = config[vecStr.at(0)];
    if (rec) {
        vecStr.erase(vecStr.begin());
        GetTheYamlValueRec(rec, vecStr, result);
        return result;
    }
    return std::vector<std::string>();
}

int main()
{
    std::vector<std::string> vecStr = {"input", "move", "z", "pos"};
    std::vector<std::string> res = GetTheYamlValue(vecStr);
    std::cout << "print de res: " << std::endl;
    for (int i = 0; i < res.size(); i++) {
        std::cout << res.at(i) << std::endl;
    }
    std::cout << "la size de rec: " << res.size() << std::endl;

//    testWriteNode("InputsConfigPersonalize");
//    testWriteNodeWithField("./srcThibault/InputsConfigPersonalize");

//    YAML::Node config = YAML::LoadFile("./srcThibault/InputsConfig.yaml");
//    if (!config)
//        std::cout << "The file couldn't be loaded!\n";

//    if (config["input"])
//        std::cout << "Inputs!\n";
//    if (config["input"]["move"])
//        std::cout << "input move!\n";
//    if (config["input"]["move"]["type"])
//        std::cout << "input move type!\n";
//    if (config["input"]["look"])
//        std::cout << "input look!\n";
//    if (config["input"]["boost"])
//        std::cout << "input boost!\n";


//    std::cout << config["input"]["move"]["z"] << std::endl;
//     std::cout << "apres le print de z:\n";
//    std::cout << config["input"]["move"]["z"]["pos"] << std::endl;

//    std::cout << "la size de pos: " << config["input"]["move"]["z"]["pos"].size() << std::endl;

//    std::cout << "la map: " << config["input"]["move"]["z"]. << std::endl;


//    for (size_t i = 0; i < config["input"]["move"]["z"].size(); i++) {
//        std::cout << "la size de [z][i]: " << config["input"]["move"]["z"][i].size() << std::endl;
//        for (size_t j = 0; j < config["input"]["move"]["z"][i].size(); j++) {
//            std::cout << config["input"]["move"]["z"][i][j] << std::endl;
//        }
//    }


//        if (config["input"]["move"]["z"]["pos"].IsMap() == true)
//            std::cout << "true map" << std::endl;
//        if (config["input"]["move"]["z"]["pos"].IsSequence() == true)
//            std::cout << "true sequence" << std::endl;
//        if (config["input"]["move"]["z"]["pos"].IsScalar() == true)
//            std::cout << "true scalar" << std::endl;
//    std::cout << config["input"]["move"]["type"] << std::endl;

//    writeInYamlFile();
    return 0;
}


//    if (config[0]["Ogre"])
//        std::cout << "[0][Ogre]\n";
//    if (config[0]["positoin"])
//        std::cout << "[0][position]\n";
//    if (config[0]["powers"])
//        std::cout << "[0][powers]\n";
//    if (config[0]["name"])
//        std::cout << "[0][name]\n";
