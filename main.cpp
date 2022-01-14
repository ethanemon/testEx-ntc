#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <algorithm>

struct field
{
    std::string id;
    std::string name;
    std::string date;
};

struct find_field
{
    std::string name;
    std::string date;

    find_field(std::string name, std::string date) {
        this->name = name;
        this->date = date;
    }

    bool operator () (const field& current_element) const
    {
        return current_element.date == date && current_element.name == name;
    }
};

void parse_file(std::vector<field> &fields, std::string path)
{

    std::ifstream input(path);

    std::regex pattern("(\\d*)(\\s\\D*\\s)(.*)");
    std::string line;
    std::smatch matches;

    while (!input.eof()) {
        std::getline(input, line);

        std::regex_search(line, matches, pattern);

        field matched_field;

        // В matches у нас находится результат регекспа
        // matches[0] - вся строка, всё остальное группы по порядку

        matched_field.id = matches[1].str();
        matched_field.name = matches[2].str();
        matched_field.date = matches[3].str();

        fields.push_back(matched_field);
    }
}
bool compareByName (const field& a, const field& b)
{
    return a.name < b.name;

}

int main()
{
    std::vector<field> fields;
    std::vector<field> unique_fields;

    parse_file(fields, "C:\\Users\\korys\\Desktop\\student_file_1.txt");
    parse_file(fields, "C:\\Users\\korys\\Desktop\\student_file_2.txt");

    for (auto const& value : fields) {
        auto it = std::find_if(unique_fields.begin(), unique_fields.end(), find_field(value.name, value.date));

        if (it == unique_fields.end()) {
            unique_fields.push_back(value);
        }
    }
    std::sort(unique_fields.begin(), unique_fields.end(), compareByName);


    for (auto const& value : unique_fields) {
        std::cout << value.id << " | " << value.name << " | " << value.date << std::endl;
    }


    return 0;
}
