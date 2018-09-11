// libraries
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
// language
#include <iostream>
#include <string>
#include <utility>

std::pair<boost::filesystem::path, int> find_file(const boost::filesystem::path& dir, std::string file_name) {
    boost::filesystem::path file_path;
    int max_version_found = -1;
    for (auto&& e : boost::filesystem::directory_iterator(dir)) {
	auto f = e.path().filename();
	std::string::size_type p = f.string().find(file_name);

	if (p == std::string::npos) {
	    continue;
	}
	auto number_str = f.string().substr(4, f.string().find(".bin") - 4);
	int version = -1;
	auto ok = boost::conversion::try_lexical_convert(number_str, version);
	if (max_version_found < version) {
	    max_version_found = version;
	    file_path = e.path();
	}
	std::cout << f.string() << std::endl;
    }

    std::pair<boost::filesystem::path, int> result;
    result.first = file_path;
    result.second = max_version_found;
    return result;
}

int main() {
    const boost::filesystem::path dir = "/dir";
    std::string file_name = "test";
    std::pair<boost::filesystem::path, int> test_file = find_file(dir, file_name);

    std::cout << test_file.first << " "
	      << std::boolalpha << test_file.second;
    return 0;
}
