#pragma once
#include <memory>
#include <string>
#include <vector>

namespace Kong
{
    class AActor;

    class CYamlParser
    {
    public:
        static void ParseYamlFile(const std::string& scene_content,
            std::vector<std::shared_ptr<AActor>>& scene_actors);
    };
}
