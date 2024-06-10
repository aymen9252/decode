#include <string>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <wchar.h>
#include <sched.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>  // Add this at the top of your source file

#include <cstdio>
#include <utility>

using namespace std;

#define strcpy_s strcpy
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#define NUMBER            0

#define CAPITAL_CHAR    1
#define SMALL_CHAR        2

#define MAX_ID_LENGTH        22
#define MAX_SUM_VALUE        MAX_ID_LENGTH * 4096

#define PART_OK            1
#define PART_NOT_IN_USE		0

#define HDD_INDEX           0
#define GU_INDEX            1
#define IO_INDEX            2
#define PRODUCT_INDEX        3
#define CAM_INDEX            4

#define BLISTER_MACHINE                "Blister"
#define CARTONING_MACHINE            "Cartoning"
#define CASEPACKER_MACHINE            "CasePacker"
#define LABELLING_MACHINE            "Labelling"
#define COUNTING_MACHINE            "Counting"
#define MICROTABLET_MACHINE          "MicroTablet"

std::vector<std::pair<long, std::vector<long>>> final_numbers;
std::vector<std::pair<long, std::vector<long>>> final_reverse_numbers;
std::vector<std::vector<std::string>> capital_char_patterns;
std::vector<std::vector<std::string>> small_char_patterns;
std::vector<std::vector<std::string>> number_patterns;
std::string dummy_pattern[2];
std::vector<std::string> three_char_combinations;
std::map<long, std::string> machine_name_index_map;

std::string getDataFromQr(std::string string1);

int main(int argc, char* argv[]) {
    std::string qrData = "252-252-252-252-252-252-252-252-252-252-252-252-252-252-f33-662-bff-bff-f33-935-e5b-9c-252-252-252-252-252-252-65d-886-abf-78c-abf-54e-92f-c05-b29-65d-886-c44-7fc-99e-cf-b98-bff-bff-bff-f7c-935-30-fcd-bff-bff-ea3-662-fcd-f33-32c-718-180-ef2-3bf-96c-4ae-a2b-9c2-252-252-252-252-886-f36-886-65d-dd1-3bc-8d0-886-886-886-886-c82-20e-4c2-c44-bb1-68d-581-16000-252-252-252-252-252-252-252-252-252-252-252-252-252-252-886-c05-65d-c05-c05-312-ff4-a9e-252-252-252-252-252-252-252-252-bff-fcd-935-f33-b0-84d-fb3-ff4-edc-fe6-a7a-4a1-fe7-668-252-252-252-252-252-252-252-252-bff-fcd-935-bff-b0-84d-fb3-ff4-edc-fe6-a7a-4a1-ff4-86e-16000-";
    std::string result = getDataFromQr(qrData);
    return 0;
}


void GetTwoCharCombination(std::vector<std::string> &result) {
	result.clear();
	result.push_back("001000");
	result.push_back("010000");
	result.push_back("111111");
	result.push_back("100111");
	
}
void PrintVector(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
}
void GetFourCharCombination(std::vector<std::string> &result) {
    PrintVector(result);
	result.clear();
	result.push_back("232301");
	result.push_back("203320");
	result.push_back("013223");
	result.push_back("030211");
	result.push_back("220312");
	result.push_back("301023");
	result.push_back("011033");
	result.push_back("100210");
	result.push_back("021112");
	result.push_back("022312");
	result.push_back("003233");
}

struct part_id {
    long validity;
    long id_type;
    std::string id;

    part_id() {
        validity = PART_OK;
    }
};

struct camera_info {
    long validity_id;
    long station_id;
    std::string camera_id;

    camera_info(long v_id, long s_id, std::string cam_id) {
        validity_id = v_id;
        station_id = s_id;
        camera_id = cam_id;
    }
};

struct part_renew_id {
    long validity;
    long id_type;
    long station_id;
    std::string id;
    std::string date;

    part_renew_id() {
        station_id = -1;
    }
};

void
GetColors(std::vector<std::string> &color_hex_value1, std::vector<std::string> &color_hex_value2,
          std::string &qr_code_string) {

    color_hex_value1.clear();
    color_hex_value2.clear();
    qr_code_string.clear();
    for (int i = 0, k = 0; i < final_numbers.size(); i++) {
        for (int j = 0; j < final_numbers[i].second.size(); j++) {
            char add_c[6];


//            _itoa_s(final_numbers[i].second[j], add_c, 6, 16);
            snprintf(add_c, 6, "%x", final_numbers[i].second[j]);


            qr_code_string.append(add_c);
            qr_code_string.append("-");
        }

        if (final_numbers[i].first < MAX_SUM_VALUE) {
            if (color_hex_value1.size() == 4) {
                int mod_value = k % 4;
                unsigned int prev_value;
                std::stringstream ss;
                ss << std::hex << color_hex_value1[mod_value].c_str();
                ss >> prev_value;
                int add_value = prev_value + final_numbers[i].first;
                char color_hex[50];
//                _itoa_s(add_value, color_hex, 10, 16);
                snprintf(color_hex, 10, "%x", add_value);


                color_hex_value1[mod_value].clear();
                color_hex_value1[mod_value].append(color_hex);
            } else {
                char color_hex[50];
//                _itoa_s(final_numbers[i].first, color_hex, 10, 16);
                snprintf(color_hex, 10, "%x", final_numbers[i].first);


                color_hex_value1.push_back(color_hex);
            }
            k++;
        }
    }

    for (int i = 0, k = 0; i < final_reverse_numbers.size(); i++) {
        if (final_reverse_numbers[i].first < MAX_SUM_VALUE) {
            if (color_hex_value2.size() == 4) {
                int mod_value = k % 4;
                unsigned int prev_value;
                std::stringstream ss;
                ss << std::hex << color_hex_value2[mod_value].c_str();
                ss >> prev_value;
                int add_value = prev_value + final_reverse_numbers[i].first;
                char color_hex[50];
//                _itoa_s(add_value, color_hex, 10, 16);
                snprintf(color_hex, 10, "%x", add_value);


                color_hex_value2[mod_value].clear();
                color_hex_value2[mod_value].append(color_hex);
            } else {
                char color_hex[50];
//                _itoa_s(final_reverse_numbers[i].first, color_hex, 10, 16);
                snprintf(color_hex, 10, "%x", final_reverse_numbers[i].first);


                color_hex_value2.push_back(color_hex);
            }
            k++;
        }
    }

    for (int i = 0; i < color_hex_value1.size(); i++) {
        if (color_hex_value1[i].length() < 6) {
            long diff = 6 - (long) color_hex_value1[i].length();
            for (int j = 0; j < diff; j++) {
                color_hex_value1[i].insert(color_hex_value1[i].begin(), '0');
            }
        }
    }

    for (int i = 0; i < color_hex_value2.size(); i++) {
        if (color_hex_value2[i].length() < 6) {
            long diff = 6 - (long) color_hex_value2[i].length();
            for (int j = 0; j < diff; j++) {
                color_hex_value2[i].insert(color_hex_value2[i].begin(), '0');
            }
        }
    }

}

void GetCharPattern(char c, int position, std::string &char_pattern) {

    int char_type = -1, index = -1;
    if (int(c) >= 65 && int(c) <= 90) {
        char_type = CAPITAL_CHAR;
        index = int(c) - 65;
    } else if (int(c) >= 97 && int(c) <= 122) {
        char_type = SMALL_CHAR;
        index = int(c) - 97;
    } else if (int(c) >= 48 && int(c) <= 57) {
        char_type = NUMBER;
        index = int(c) - 48;
    }

    if (char_type == NUMBER) {
        if (number_patterns.size() < position) {
            char_pattern = dummy_pattern[position];
        } else {
            char_pattern = number_patterns[position][index];
        }
    } else if (char_type == CAPITAL_CHAR) {
        if (capital_char_patterns.size() < position) {
            char_pattern = dummy_pattern[position];
        } else {
            char_pattern = capital_char_patterns[position][index];
        }
    } else if (char_type == SMALL_CHAR) {
        if (small_char_patterns.size() < position) {
            char_pattern = dummy_pattern[position];
        } else {
            char_pattern = small_char_patterns[position][index];
        }
    } else {
        char_pattern = dummy_pattern[position];
    }
}

void FindNumbers(std::vector<std::string> &string_for_encoding, bool append_numbers = false) {

    if (!append_numbers) {
        final_numbers.clear();
        final_reverse_numbers.clear();
    }

    if (string_for_encoding.size() == 0) {
        return;
    }

    for (int id = 0; id < string_for_encoding.size(); id += 2) {
        std::pair<long, std::vector<long>> numbers_per_string_pair;
        numbers_per_string_pair.first = 0;
        for (int i = 0; i < string_for_encoding[id].size(); i++) {
            std::string added_pattern;

            std::string char_pattern1;
            char c1 = string_for_encoding[id][i];
            GetCharPattern(c1, 0, char_pattern1);

            std::string char_pattern2;
            char c2 = string_for_encoding[id + 1][i];
            GetCharPattern(c2, 1, char_pattern2);

            for (int j = 0; j < char_pattern1.size(); j++) {
                char c[2] = "\0";
                c[0] = char_pattern1[j];
                int n1 = atoi(c);
                c[0] = char_pattern2[j];
                int n2 = atoi(c);
                char add_c[2];
//                _itoa_s(n1 + n2, add_c, 2, 10);
                snprintf(add_c, 2, "%d", n1 + n2);


                added_pattern.push_back(add_c[0]);
            }

            std::vector<std::string>::iterator iter = std::find(three_char_combinations.begin(),
                                                                three_char_combinations.end(),
                                                                added_pattern);
            int dist = (int) std::distance(three_char_combinations.begin(), iter);

            numbers_per_string_pair.second.push_back(dist);
            numbers_per_string_pair.first += dist;
        }
        final_numbers.push_back(numbers_per_string_pair);

        std::pair<long, std::vector<long>> numbers_per_string_pair_reverse;
        numbers_per_string_pair_reverse.first = 0;
        for (int i = (int) string_for_encoding[id].size() - 1, j = 0; i >= 0; i--, j++) {
            std::string added_pattern;

            std::string char_pattern1;
            char c1 = string_for_encoding[id][i];
            GetCharPattern(c1, 0, char_pattern1);

            std::string char_pattern2;
            char c2 = string_for_encoding[id + 1][j];
            GetCharPattern(c2, 1, char_pattern2);

            for (int k = 0; k < char_pattern1.size(); k++) {
                char c[2] = "\0";
                c[0] = char_pattern1[k];
                int n1 = atoi(c);
                c[0] = char_pattern2[k];
                int n2 = atoi(c);
                char add_c[2];
//                _itoa_s(n1 + n2, add_c, 2, 10);
                snprintf(add_c, 2, "%d", n1 + n2);


                added_pattern.push_back(add_c[0]);
            }

            std::vector<std::string>::iterator iter = std::find(three_char_combinations.begin(),
                                                                three_char_combinations.end(),
                                                                added_pattern);
            int dist = (int) std::distance(three_char_combinations.begin(), iter);

            numbers_per_string_pair_reverse.second.push_back(dist);
            numbers_per_string_pair_reverse.first += dist;
        }
        final_reverse_numbers.push_back(numbers_per_string_pair_reverse);
    }
    std::vector<long> eof;
    eof.push_back(MAX_SUM_VALUE);
    final_numbers.push_back(std::pair<long, std::vector<long>>(MAX_SUM_VALUE, eof));
    final_reverse_numbers.push_back(std::pair<long, std::vector<long>>(MAX_SUM_VALUE, eof));
}

void GetCurrentDate(std::string &current_date) {

    current_date.clear();
    time_t t = time(0);
    struct tm buf;

//    buf = localtime(&t);

//        localtime_s(&buf, &t);

    localtime_r(reinterpret_cast<const time_t *>(&buf), reinterpret_cast<tm *>(&t));

    char temp_c[10];

    snprintf(temp_c, 10, "%d", buf.tm_mday);

    if (temp_c[1] == '\0') {
        current_date.append("0");
    }
    current_date.append(temp_c);

//    _itoa_s(buf.tm_mon + 1, temp_c, 10, 10);
    snprintf(temp_c, 10, "%d", buf.tm_mon + 1);

    if (temp_c[1] == '\0') {
        current_date.append("0");
    }
    current_date.append(temp_c);

//    _itoa_s(buf.tm_year + 1900, temp_c, 10, 10);
    snprintf(temp_c, 10, "%d", buf.tm_year + 1900);


    current_date.append(temp_c);
}

void GetValidSerialId(std::string &input, std::string &output, long max_serial_lenght) {

    output.clear();
    for (int i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if ((int(c) >= 65 && int(c) <= 90) ||
            (int(c) >= 97 && int(c) <= 122) ||
            (int(c) >= 48 && int(c) <= 57)/* ||
										  int(c) == 45 ||
										  int(c) == 47 ||
										  int(c) == 92*/) {
            output.append(&c, 1);
        }
    }
    long diff = max_serial_lenght - (long) output.size();
    if (output.size() <= max_serial_lenght) {
        for (int i = 0; i < diff; i++) {
            output.insert(output.begin(), '~');
        }
    } else {
        long ignore_length = (long) output.length() - max_serial_lenght;
        for (int i = 0; i < ignore_length; i++) {
            output.pop_back();
        }
    }
}



void
GetValidSerialId2(long validity_id, long hardware_index, std::string &input, std::string &output,
                  long max_serial_lenght) {

    output.clear();

    char c[10];
//    _itoa_s(hardware_index, c, 10, 10);
    snprintf(c, 10, "%d", hardware_index);

    output.insert(output.begin(), c[0]);

//    _itoa_s(validity_id, c, 10, 10);
    snprintf(c, 10, "%x", validity_id);
    output.insert(output.begin(), c[0]);

    for (int i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if ((int(c) >= 65 && int(c) <= 90) ||
            (int(c) >= 97 && int(c) <= 122) ||
            (int(c) >= 48 && int(c) <= 57)) {
            output.append(&c, 1);
        }
    }

    long diff = max_serial_lenght - (long) output.size();
    if (output.size() <= max_serial_lenght) {
        for (int i = 0; i < diff; i++) {
            output.insert(output.begin(), '~');
        }
    } else {
        long ignore_length = (long) output.length() - max_serial_lenght;
        for (int i = 0; i < ignore_length; i++) {
            output.pop_back();
        }
    }
}

void PrepareStringForEncoding(std::string &invoice_id, std::string &po_id, long machine_id,
                              part_id &hdd_id,
                              part_id &gu_id, part_id &io_id, std::vector<camera_info> &camera_ids,
                              part_id &product_id,
                              std::vector<std::string> &string_for_encoding,
                              const std::string &date_time) {


    std::string current_date_time;
    if (date_time == "") {
        GetCurrentDate(current_date_time);
    } else {
        current_date_time = date_time;
    }

    string_for_encoding.clear();

    //INSERTING DUMMY CHAR '~' TO MAKE ALL THE SERIAL NUMBERS OF SAME LENGTH
    std::string valid_id = "";

    GetValidSerialId(current_date_time, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    GetValidSerialId(invoice_id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    GetValidSerialId(po_id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    GetValidSerialId2(hdd_id.validity, HDD_INDEX, hdd_id.id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    GetValidSerialId2(gu_id.validity, GU_INDEX, gu_id.id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    GetValidSerialId2(io_id.validity, IO_INDEX, io_id.id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    GetValidSerialId2(product_id.validity, PRODUCT_INDEX, product_id.id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);

    for (int i = 0; i < camera_ids.size(); i++) {
        std::string camera_id_with_station_id = camera_ids[i].camera_id;
        char c[10];
//        _itoa_s(camera_ids[i].station_id, c, 10, 10);
        snprintf(c, 10, "%d", camera_ids[i].station_id);

        camera_id_with_station_id.insert(camera_id_with_station_id.begin(), c[0]);
//        _itoa_s(machine_id, c, 10, 10);
        snprintf(c, 10, "%d", machine_id);

        camera_id_with_station_id.insert(camera_id_with_station_id.begin(), c[0]);

        GetValidSerialId2(camera_ids[i].validity_id, CAM_INDEX, camera_id_with_station_id, valid_id,
                          MAX_ID_LENGTH);
        string_for_encoding.push_back(valid_id);
        //string_for_encoding.push_back(valid_id);
    }

    //MAKING DUMMY STRING ID OF MAX SERIAL KEY LENGTH
    std::string dummy_id;
    for (int i = 0; i < MAX_ID_LENGTH; i++) {
        dummy_id.push_back('~');
    }

    long total_given_ids = 7 + (long) camera_ids.size();
    long total_ids = total_given_ids + (total_given_ids % 2);
    total_ids = total_ids < 8 ? 8 : total_ids;
    for (int i = 0; i < total_ids - total_given_ids; i++) {
        string_for_encoding.push_back(dummy_id);
    }
}




void RemoveDummyChar(std::string &input, std::string &output) {

    output.clear();
    for (int i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if (c != '~') {
            output.append(&c, 1);
        }
    }
}



void
RemoveDummyChar(std::string &input, std::string &output, long &hardware_id, long &validity_id) {

    bool first_valid_char_taken = false;
    bool second_valid_char_taken = false;
    output.clear();
    for (int i = 0; i < input.length(); i++) {
        char c[2] = "\0";
        c[0] = input.at(i);
        if (c[0] != '~') {
            if (!first_valid_char_taken) {
                validity_id = atoi(c);
                first_valid_char_taken = true;
                continue;
            }
            if (!second_valid_char_taken) {
                hardware_id = atoi(c);
                second_valid_char_taken = true;
                continue;
            }
            output.append(c, 1);
        }
    }


}


void GetCharFromPattern(std::string &char_pattern, int position, char &c) {
    
std::vector<std::string>::iterator iter1 = std::find(capital_char_patterns[position].begin(),
                                                     capital_char_patterns[position].end(),
                                                     char_pattern);


    if (iter1 == capital_char_patterns[position].end()) {
        std::vector<std::string>::iterator iter2 = std::find(small_char_patterns[position].begin(),
                                                             small_char_patterns[position].end(),
                                                             char_pattern);
        if (iter2 == small_char_patterns[position].end()) {
            std::vector<std::string>::iterator iter3 = std::find(number_patterns[position].begin(),
                                                                 number_patterns[position].end(),
                                                                 char_pattern);
            if (iter3 == number_patterns[position].end()) {
                if (dummy_pattern[position] == char_pattern) {
                    c = '~';
                }
            } else {
                long dist = long(iter3 - number_patterns[position].begin());
                long ascii = 48 + dist;
                c = (char) ascii;
            }
        } else {
            long dist = long(iter2 - small_char_patterns[position].begin());
            long ascii = 97 + dist;
            c = (char) ascii;
        }
    } else {
        long dist = long(iter1 - capital_char_patterns[position].begin());
        long ascii = 65 + dist;
        c = (char) ascii;
    }
}

void GetCharPairFromTuple(std::string &tuple, char &char1, char &char2) {

    unsigned int int_value;
    std::stringstream ss;
    ss << std::hex << tuple.c_str();
    ss >> int_value;
    


    auto jump = three_char_combinations.begin();
    std::advance(jump, int_value);
    std::string added_string = jump->c_str();

    std::string string1, string2;
    
                    // std::printf("\n Tuple: %s\n", tuple.c_str());
                    // std::printf("\n Tuple: %d\n", added_string.size());

    for (int i = 0; i < added_string.size(); i++) {
                   

        char c[2] = "\0";
        c[0] = added_string[i];
        int x = atoi(c);
        //   std::printf("Tuple: %d\n", x);
        if (x == 0) {
            string1.append("0");
            string2.append("0");
        } else if (x == 1) {
            string1.append("1");
            string2.append("0");
        } else if (x == 2) {
            string1.append("0");
            string2.append("2");
        } else if (x == 3) {
            string1.append("1");
            string2.append("2");
        }
                //   std::printf("s1: %s,  S2 : %s\n", string1.c_str(),string2.c_str());

    }

    GetCharFromPattern(string1, 0, char1);
    GetCharFromPattern(string2, 1, char2);
}

std::string
RetriveInfoFromQR(std::string &qr_string, std::string &first_gen_date_time, std::string &invoice_id,
                  std::string &po_id,
                  long &machine_id, part_id &hdd_id, part_id &gu_id, part_id &io_id,
                  part_id &product_id, std::vector<camera_info> &camera_ids,
                  std::vector<part_renew_id> &renew_ids,
                  std::vector<std::string> &color_hex_value1,
                  std::vector<std::string> &color_hex_value2) {
    std::string lic_info = "";
    if (qr_string.length() < 1) {
//        return false;
        return lic_info;
    }

    first_gen_date_time.clear();
    invoice_id.clear();
    po_id.clear();
    hdd_id.id.clear();
    gu_id.id.clear();
    io_id.id.clear();
    product_id.id.clear();
    camera_ids.clear();
    renew_ids.clear();

    std::vector<std::string> serial_string;
    std::vector<std::vector<std::string>> serial_strings;
    long count_dash = 0;
    std::string string1 = "", string2 = "";
    std::string::iterator pre_seperator_iter = qr_string.begin();

    while (pre_seperator_iter != qr_string.end()) {
        std::string::iterator seperator_iter = std::find(pre_seperator_iter, qr_string.end(), '-');
        if (seperator_iter != qr_string.end()) {
            std::string tuple;
            tuple.assign(pre_seperator_iter, seperator_iter);
            char max_hex[6];
//            _itoa_s(MAX_SUM_VALUE, max_hex, 6, 16);
            snprintf(max_hex, 6, "%x", MAX_SUM_VALUE);

            if (tuple == max_hex) {
                serial_strings.push_back(serial_string);
                serial_string.clear();
                pre_seperator_iter = ++seperator_iter;
                continue;
            }
            char char1, char2;
            GetCharPairFromTuple(tuple, char1, char2);
            // printf("Char1 %c , char2 %c",char1,char2);
            pre_seperator_iter = ++seperator_iter;
            count_dash++;
            if (count_dash < MAX_ID_LENGTH) {
                string1.append(1, char1);
                string2.append(1, char2);
            } else {
                string1.append(1, char1);
                string2.append(1, char2);
                count_dash = 0;
                serial_string.push_back(string1);
                serial_string.push_back(string2);
                string1.clear();
                string2.clear();
            }
        }
    }

    for (int renew_index = 0; renew_index < serial_strings.size(); renew_index++) {
        if (renew_index == 0) {    //Primary Serial Information
            RemoveDummyChar(serial_strings[renew_index][0], first_gen_date_time);
            RemoveDummyChar(serial_strings[renew_index][1], invoice_id);
            RemoveDummyChar(serial_strings[renew_index][2], po_id);
            lic_info.append("\nINVOIC_NO : " + invoice_id);
            lic_info.append("\nPO_ID : " + po_id);
            RemoveDummyChar(serial_strings[renew_index][3], hdd_id.id, hdd_id.id_type,
                            hdd_id.validity);
            RemoveDummyChar(serial_strings[renew_index][4], gu_id.id, gu_id.id_type,
                            gu_id.validity);
            RemoveDummyChar(serial_strings[renew_index][5], io_id.id, io_id.id_type,
                            io_id.validity);
            RemoveDummyChar(serial_strings[renew_index][6], product_id.id, product_id.id_type,
                            product_id.validity);
//            lic_info.append("\nPRODUCT_ID : " + po_id);
            for (int i = 7; i < serial_strings[renew_index].size(); i++) {
                std::string camera_serial;
                long part_id = -2, validity_id = -2;
                RemoveDummyChar(serial_strings[renew_index][i], camera_serial, part_id,
                                validity_id);
                if (camera_serial.length() <= 0) {
                    continue;
                }
                char c[2] = "\0";
                c[0] = camera_serial.at(0);
                machine_id = atoi(c);
                c[0] = camera_serial.at(1);
                long station_id = atoi(c);

                camera_info cam_info(validity_id, station_id, "");
                for (int j = 2; j < camera_serial.length(); j++) {
                    char c = camera_serial.at(j);
                    cam_info.camera_id.append(&c, 1);
                }
                camera_ids.push_back(cam_info);
//                lic_info.append("\nCAMERA_NO : " + camera_serial);

            }
        } else {    //Secondary Serial Information
            for (int j = 0; j < serial_strings[renew_index].size(); j += 2) {
                part_renew_id renew_id;
                RemoveDummyChar(serial_strings[renew_index][j], renew_id.id, renew_id.id_type,
                                renew_id.validity);
                if (renew_id.id_type == CAM_INDEX) {
                    char c[2] = "\0";
                    c[0] = renew_id.id.at(1);
                    renew_id.station_id = atoi(c);

                    std::string temp_string = "";
                    for (int j = 2; j < renew_id.id.length(); j++) {
                        char c = renew_id.id.at(j);
                        temp_string.append(&c, 1);
                    }
                    renew_id.id = temp_string;
                }
                RemoveDummyChar(serial_strings[renew_index][j + 1], renew_id.date);
                renew_ids.push_back(renew_id);
//                lic_info.append("\nCAMERA_NO : " + renew_id.id);
            }
        }
    }

    std::vector<std::string> string_for_encoding;
    std::string qr_code_string;
    PrepareStringForEncoding(invoice_id, po_id, machine_id, hdd_id, gu_id, io_id,
                             camera_ids, product_id, string_for_encoding, first_gen_date_time);
    FindNumbers(string_for_encoding);
    GetColors(color_hex_value1, color_hex_value2, qr_code_string);

    if (renew_ids.size() == 0) {
        return lic_info;
    }

    for (int i = 0; i < renew_ids.size(); i++) {
        std::string valid_id;
        std::string id = renew_ids[i].id;
        if (renew_ids[i].id_type == CAM_INDEX) {
            char c[10];
//            _itoa_s(renew_ids[i].station_id, c, 10, 10);
            snprintf(c, 10, "%d", renew_ids[i].station_id);

            id.insert(id.begin(), c[0]);
//            _itoa_s(machine_id, c, 10, 10);
            snprintf(c, 10, "%d", machine_id);

            id.insert(id.begin(), c[0]);
        }

        GetValidSerialId2(renew_ids[i].validity, renew_ids[i].id_type, id, valid_id, MAX_ID_LENGTH);
        string_for_encoding.push_back(valid_id);
        GetValidSerialId(renew_ids[i].date, valid_id, MAX_ID_LENGTH);
        string_for_encoding.push_back(valid_id);
    }
    std::string dummy_id;
    for (int i = 0; i < MAX_ID_LENGTH; i++) {
        dummy_id.push_back('~');
    }

    long new_addition_size = (long) renew_ids.size() * 2;
    long total_ids = new_addition_size + (new_addition_size % 2);
    for (int i = 0; i < total_ids - new_addition_size; i++) {
        string_for_encoding.push_back(dummy_id);
    }
    FindNumbers(string_for_encoding);
    GetColors(color_hex_value1, color_hex_value2, qr_code_string);
    return lic_info;
}

void Initialize() {

    machine_name_index_map.insert({0, BLISTER_MACHINE});
    machine_name_index_map.insert({1, CARTONING_MACHINE});
    machine_name_index_map.insert({2, CASEPACKER_MACHINE});
    machine_name_index_map.insert({3, LABELLING_MACHINE});
    machine_name_index_map.insert({4, COUNTING_MACHINE});
    machine_name_index_map.insert({5, MICROTABLET_MACHINE});



    capital_char_patterns.clear();
    small_char_patterns.clear();
    number_patterns.clear();
    three_char_combinations.clear();

    //GENERATING CHAR PATTERN
    std::string chars;
    chars.push_back('0');
    chars.push_back('1');
    std::vector<std::string> result1;
    GetTwoCharCombination(result1);

    chars.clear();
    chars.push_back('0');
    chars.push_back('1');
    chars.push_back('2');
    chars.push_back('3');
    //three_char_combinations = PermuteString(6, chars);
    GetFourCharCombination(three_char_combinations);

    long total_numbers = 10, number_count = 0;
    long total_capital_chars = 26, cap_char_count = 0;
    long total_small_chars = 26, small_char_count = 0;

    if (result1.size() == 64) {
        number_patterns.resize(2);
        capital_char_patterns.resize(2);
        small_char_patterns.resize(2);

        std::vector<std::string>::iterator result_iter1 = result1.begin();
        for (; result_iter1 != result1.end(); result_iter1++) {
            if (result_iter1->c_str() != "000000") {

                std::string second_string = result_iter1->data();
                for (int i = 0; i < second_string.size(); i++) {
                    if (second_string[i] == '1') {
                        second_string[i] = '2';
                    }
                }

                if (number_count < total_numbers) {
                    number_patterns[0].push_back(result_iter1->data());
                    number_patterns[1].push_back(second_string);
                    number_count++;
                } else if (cap_char_count < total_capital_chars) {
                    capital_char_patterns[0].push_back(result_iter1->data());
                    capital_char_patterns[1].push_back(second_string);
                    cap_char_count++;
                } else if (small_char_count < total_small_chars) {
                    small_char_patterns[0].push_back(result_iter1->data());
                    small_char_patterns[1].push_back(second_string);
                    small_char_count++;
                } else {
                    dummy_pattern[0] = result_iter1->data();
                    dummy_pattern[1] = second_string;
                }
            }
        }
    }
}

std::string GetMachineName(long machine_id) {

    auto iter = machine_name_index_map.begin();
    while (iter != machine_name_index_map.end()) {
        if (iter->first == machine_id) {
            return iter->second;
        }
        iter++;
    }
    return "";
}
std::string getProductNumber(std::string cameraNo) {
    std::string product_code = cameraNo;
    unsigned int product_code_value;
    std::stringstream ss;
    int lic_value;
    ss << std::hex << product_code;
    ss >> product_code_value;

    std::string product_number = "";
    for (int product_index = 0; product_index < 64; product_index++) {
        lic_value = (product_code_value >> product_index) & 0x01;
        if (lic_value == 1) {
            if (product_number == "") {
                product_number = product_number + std::to_string(product_index);
            } else {
                product_number = product_number + "," + std::to_string(product_index);
            }

        }
        //lic_value = 0 or 1;
    }
    return product_number;
}












void PrepareAppendStringForEncoding(long machine_id, part_id &hdd_id, part_id &gu_id, part_id &io_id,
	std::vector<camera_info> &camera_ids, part_id &product_id,
	std::vector<std::string> &string_for_encoding) {

	std::string current_date_time, current_date_time2;
	GetCurrentDate(current_date_time2);

	string_for_encoding.clear();

	//INSERTING DUMMY CHAR '~' TO MAKE ALL THE SERIAL NUMBERS OF SAME LENGTH
std::string valid_id = "";

	GetValidSerialId(current_date_time2, current_date_time, MAX_ID_LENGTH);

	long total_pair_inserted = 0;
	if (hdd_id.validity == PART_OK) {
		GetValidSerialId2(PART_OK, HDD_INDEX, hdd_id.id, valid_id, MAX_ID_LENGTH);
		string_for_encoding.push_back(valid_id);
		string_for_encoding.push_back(current_date_time);
		total_pair_inserted += 2;
	}

	if (gu_id.validity == PART_OK) {
		GetValidSerialId2(PART_OK, GU_INDEX, gu_id.id, valid_id, MAX_ID_LENGTH);
		string_for_encoding.push_back(valid_id);
		string_for_encoding.push_back(current_date_time);
		total_pair_inserted += 2;
	}

	if (io_id.validity == PART_OK) {
		GetValidSerialId2(PART_OK, IO_INDEX, io_id.id, valid_id, MAX_ID_LENGTH);
		string_for_encoding.push_back(valid_id);
		string_for_encoding.push_back(current_date_time);
		total_pair_inserted += 2;
	}

	if (product_id.validity == PART_OK) {
		GetValidSerialId2(PART_OK, PRODUCT_INDEX, product_id.id, valid_id, MAX_ID_LENGTH);
		string_for_encoding.push_back(valid_id);
		string_for_encoding.push_back(current_date_time);
		total_pair_inserted += 2;
	}

// 	for (int i = 0; i < camera_ids.size(); i++) {
// 		std::string camera_id_with_station_id = camera_ids[i].camera_id;
// 		char c[10];
// 		_itoa_s(camera_ids[i].station_id, c, 10, 10);
// 		camera_id_with_station_id.insert(camera_id_with_station_id.begin(), c[0]);
// 		_itoa_s(machine_id, c, 10, 10);
// 		camera_id_with_station_id.insert(camera_id_with_station_id.begin(), c[0]);

// 		GetValidSerialId(PART_OK, CAM_INDEX, camera_id_with_station_id, valid_id, MAX_ID_LENGTH);
// 		string_for_encoding.push_back(valid_id);
// 		string_for_encoding.push_back(current_date_time);
// 		total_pair_inserted += 2;
// 	}

for (size_t i = 0; i < camera_ids.size(); i++) {
        std::string camera_id_with_station_id = camera_ids[i].camera_id;
        
        // Convert station_id to string and insert at the beginning
        std::string station_id_str = std::to_string(camera_ids[i].station_id);
        camera_id_with_station_id.insert(0, station_id_str);

        // Convert machine_id to string and insert at the beginning
        std::string machine_id_str = std::to_string(machine_id);
        camera_id_with_station_id.insert(0, machine_id_str);

        GetValidSerialId2(PART_OK, CAM_INDEX, camera_id_with_station_id, valid_id, MAX_ID_LENGTH);
        string_for_encoding.push_back(valid_id);
        string_for_encoding.push_back(current_date_time);
        total_pair_inserted += 2;
    }

	//MAKING DUMMY STRING ID OF MAX SERIAL KEY LENGTH
	std::string dummy_id;
	for (int i = 0; i < MAX_ID_LENGTH; i++) {
		dummy_id.push_back('~');
	}

	long total_ids = total_pair_inserted + (total_pair_inserted % 2);
	for (int i = 0; i < total_ids - total_pair_inserted; i++) {
		string_for_encoding.push_back(dummy_id);
	}
}

void DiscardInvalidChar(std::string &input, std::string &output, long max_serial_lenght) {

	output.clear();
	for (int i = 0; i < input.length(); i++) {
		char c = input.at(i);
		if ((int(c) >= 65 && int(c) <= 90) || (int(c) >= 97 && int(c) <= 122) || (int(c) >= 48 && int(c) <= 57)) {
			output.append(&c, 1);
		}
	}
	long diff = max_serial_lenght - (long)output.size();
	if (output.size() > max_serial_lenght) {
		long ignore_length = (long)output.length() - max_serial_lenght;
		for (int i = 0; i < ignore_length; i++) {
			output.pop_back();
		}
	}
}


bool is_not_digit(char c) {
	return !std::isdigit(c);
}


bool numeric_string_compare(const std::string& s1, const std::string& s2) {
	// handle empty strings...

	std::string::const_iterator it1 = s1.begin(), it2 = s2.begin();

	if (std::isdigit(s1[0]) && std::isdigit(s2[0])) {
		int n1, n2;
		std::stringstream ss(s1);
		ss >> n1;
		ss.clear();
		ss.str(s2);
		ss >> n2;

		if (n1 != n2) return n1 < n2;

		it1 = std::find_if(s1.begin(), s1.end(), is_not_digit);
		it2 = std::find_if(s2.begin(), s2.end(), is_not_digit);
	}

	return std::lexicographical_compare(it1, s1.end(), it2, s2.end());
}

void SortCameraId(std::vector<std::pair<long, std::string>> &camera_ids) {
	for (int i = 0; i < camera_ids.size(); i++) {
		for (int j = i + 1; j < camera_ids.size(); j++) {
			if (numeric_string_compare(camera_ids[i].second, camera_ids[j].second)) {
				std::pair<long, std::string> temp_pair;
				temp_pair = camera_ids[j];
				camera_ids[j] = camera_ids[i];
				camera_ids[i] = temp_pair;
			}
		}
	}
}

bool StringMatching(std::string &key_word, std::string &string) {
	std::string out_string;
	DiscardInvalidChar(string, out_string, MAX_ID_LENGTH);
	if (key_word.length() > out_string.length()) {
		return false;
	}
	for (int i = 0; i < key_word.length(); i++) {
		if (key_word.at(i) != out_string.at(i)) {
			return false;
		}
	}
	return true;
}


bool RenewLicense(std::string &qr_string, long machine_id,
                  std::string &hdd_id_string, std::string &gu_id_string, std::string &io_id_string,
                  std::vector<std::pair<long, std::string>> &camera_ids, std::string &product_id_string,
                  std::vector<std::string> &color_hex_value1, std::vector<std::string> &color_hex_value2,
                  std::string &qr_code_string, const std::string &date_time) {
    if (hdd_id_string.empty() || gu_id_string.empty() || io_id_string.empty() || camera_ids.empty() || product_id_string.empty() || qr_string.empty()) {
        return false;
    }

    // Local variable names changed to avoid shadowing
    part_id hddId, guId, ioId, productId;
    std::vector<camera_info> cameraInfos;
    std::vector<part_renew_id> renewIds;
    std::string first_gen_date_time, invoice_id, po_id;

    // Assuming RetriveInfoFromQR is correctly defined and linked
    RetriveInfoFromQR(qr_string, first_gen_date_time, invoice_id, po_id, machine_id, hddId, guId, ioId, productId, cameraInfos, renewIds, color_hex_value1, color_hex_value2);


	bool hdd_id_found = false, gu_id_found = false, io_id_found = false, product_id_found = false;
	std::string valid_id;
	hddId.validity = PART_OK;
	DiscardInvalidChar(hdd_id_string, valid_id, MAX_ID_LENGTH - 2);
	if (valid_id != hddId.id) {
		hddId.validity = PART_NOT_IN_USE;
		for (int i = 0; i < renewIds.size(); i++) {
			if (renewIds[i].id_type == HDD_INDEX) {
				if (renewIds[i].id == valid_id && renewIds[i].validity == PART_OK) {
					hdd_id_found = true;
					break;
				} else{
					renewIds[i].validity = PART_NOT_IN_USE;
				}
			}
		}
	} else {
		hdd_id_found = true;
	}

	guId.validity = PART_OK;
	DiscardInvalidChar(gu_id_string, valid_id, MAX_ID_LENGTH - 2);
	if (valid_id != guId.id) {
		guId.validity = PART_NOT_IN_USE;
		for (int i = 0; i < renewIds.size(); i++) {
			if (renewIds[i].id_type == GU_INDEX) {
				if (renewIds[i].id == valid_id && renewIds[i].validity == PART_OK) {
					gu_id_found = true;
					break;
				} else { 
					renewIds[i].validity = PART_NOT_IN_USE;
				}
			}
		}
	} else {
		gu_id_found = true;
	}

	ioId.validity = PART_OK;
	DiscardInvalidChar(io_id_string, valid_id, MAX_ID_LENGTH - 2);
	if (valid_id != ioId.id) {
		ioId.validity = PART_NOT_IN_USE;
		for (int i = 0; i < renewIds.size(); i++) {
			if (renewIds[i].id_type == IO_INDEX) {
				if (renewIds[i].id == valid_id && renewIds[i].validity == PART_OK) {
					io_id_found = true;
					break;
				} else{
					renewIds[i].validity = PART_NOT_IN_USE;
				}
			}
		}
	} else {
		io_id_found = true;
	}

	productId.validity = PART_OK;
	DiscardInvalidChar(product_id_string, valid_id, MAX_ID_LENGTH - 2);
	if (valid_id != productId.id) {
		productId.validity = PART_NOT_IN_USE;
		for (int i = 0; i < renewIds.size(); i++) {
			if (renewIds[i].id_type == PRODUCT_INDEX) {
				if (renewIds[i].id == valid_id && renewIds[i].validity == PART_OK) {
					product_id_found = true;
					break;
				} else{
					renewIds[i].validity = PART_NOT_IN_USE;
				}
			}
		}
	} else {
		product_id_found = true;
	}

	std::vector<std::string> string_for_encoding;
	std::vector<camera_info> cam_info;
	long previous_cam_count = 0;
	for (int i = 0; i < camera_ids.size(); i++) {
		bool camera_found = false;
		int new_cam_index = -1;
		for (int j = 0; j < camera_ids.size(); j++) {
			DiscardInvalidChar(camera_ids[j].second, valid_id, MAX_ID_LENGTH - 4);
			if (cameraInfos[i].camera_id == valid_id && cameraInfos[i].validity_id == PART_OK) {
				camera_found = true;
				new_cam_index = j;
				break;
			}
		}
		if (!camera_found) {
			cam_info.push_back(camera_info(PART_NOT_IN_USE, cameraInfos[i].station_id, cameraInfos[i].camera_id));
		}
		else {
			cam_info.push_back(camera_info(PART_OK, camera_ids[new_cam_index].first, cameraInfos[i].camera_id));
			previous_cam_count++;
		}
	}
	for (int i = 0; i < renewIds.size(); i++) {
		if (renewIds[i].id_type == CAM_INDEX) {
			bool camera_found = false;
			int ref_id = 0;
			for (int j = 0; j < camera_ids.size(); j++) {
				DiscardInvalidChar(camera_ids[j].second, valid_id, MAX_ID_LENGTH - 4);
				if (renewIds[i].id == valid_id && renewIds[i].validity == PART_OK) {
					ref_id = j;
					camera_found = true;
					break;
				}
			}
			if (!camera_found) {
				renewIds[i].validity = PART_NOT_IN_USE;
			} else {
				renewIds[i].validity = PART_OK;
				renewIds[i].station_id = camera_ids[ref_id].first;
				previous_cam_count++;
			}
		}
	}

	bool new_camera_added = false;
	if (camera_ids.size() - previous_cam_count > 0) {
		new_camera_added = true;
	}

	PrepareStringForEncoding(invoice_id, po_id, machine_id, hddId, guId, ioId,
		cam_info, productId, string_for_encoding, first_gen_date_time);
	FindNumbers(string_for_encoding);
	GetColors(color_hex_value1, color_hex_value2, qr_code_string);

	if (hdd_id_found && gu_id_found && io_id_found && product_id_found && !new_camera_added && renewIds.size() <= 0) {
// 		return GetQRImage(qr_code_string);
	}
	else {

string_for_encoding.clear();
for (int i = 0; i < renewIds.size(); i++) {
    std::string valid_id;
    std::string id = renewIds[i].id;
    if (renewIds[i].id_type == CAM_INDEX){
        id.insert(id.begin(), std::to_string(renewIds[i].station_id)[0]);
        id.insert(id.begin(), std::to_string(machine_id)[0]);
    }
    GetValidSerialId2(renewIds[i].validity, renewIds[i].id_type, id, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);
    GetValidSerialId(renewIds[i].date, valid_id, MAX_ID_LENGTH);
    string_for_encoding.push_back(valid_id);
}
std::string dummy_id(MAX_ID_LENGTH, '~');


		long new_addition_size = (long)renewIds.size() * 2;
		long total_ids = new_addition_size + (new_addition_size % 2);
		for (int i = 0; i < total_ids - new_addition_size; i++) {
			string_for_encoding.push_back(dummy_id);
		}
		FindNumbers(string_for_encoding, true);
		//GetColors(color_hex_value1, color_hex_value2, qr_code_string);

		std::vector<camera_info> new_cam_info;
		for (int i = 0; i < camera_ids.size(); i++) {
			bool camera_found = false;
			DiscardInvalidChar(camera_ids[i].second, valid_id, MAX_ID_LENGTH - 4);
			for (int j = 0; j < cameraInfos.size(); j++) {
				if (cameraInfos[j].camera_id == valid_id && cameraInfos[j].validity_id == PART_OK) {
					camera_found = true;
					break;
				}
			}
			for (int j = 0; j < renewIds.size(); j++) {
				if (renewIds[j].id_type == CAM_INDEX) {
					if (renewIds[j].id == valid_id && renewIds[j].validity == PART_OK) {
						camera_found = true;
						break;
					}
				}
			}
			if (!camera_found) {
				new_cam_info.push_back(camera_info(PART_OK, camera_ids[i].first, camera_ids[i].second));
			}
		}

		part_id _hddId, __gu_id, _ioId, __product_id;
		_hddId.validity = hdd_id_found ? PART_NOT_IN_USE : PART_OK;
		_hddId.id = hdd_id_string;
		__gu_id.validity = gu_id_found ? PART_NOT_IN_USE : PART_OK;
		__gu_id.id = gu_id_string;
		_ioId.validity = io_id_found ? PART_NOT_IN_USE : PART_OK;
		_ioId.id = io_id_string;
		__product_id.validity = product_id_found ? PART_NOT_IN_USE : PART_OK;
		__product_id.id = product_id_string;
		std::vector<std::string> string_to_append;
		PrepareAppendStringForEncoding(machine_id, _hddId, __gu_id, _ioId, 
			new_cam_info, __product_id, string_to_append);
		FindNumbers(string_to_append, true);
		GetColors(color_hex_value1, color_hex_value2, qr_code_string);
// 		if (!GetQRImage(qr_code_string)) {
// 			return GetLicense(_invoice_id, _po_id, machine_id, hdd_id, gu_id, io_id, camera_ids, product_id, color_hex_value1, color_hex_value2, qr_code_string, date_time);
// 		} else {
			return true;
// 		}
	}

	return false;
}



bool GetLicense(std::string &invoice_id, std::string &po_id, long machine_id, std::string &hdd_id, std::string &gu_id, std::string &io_id,
	std::vector<std::pair<long, std::string>> &camera_ids, std::string &product_id,
	std::vector<std::string> &color_hex_value1, std::vector<std::string> &color_hex_value2,
	 std::string &qr_code_string, const std::string &date_time) {

	if (hdd_id.length() <= 0 || gu_id.length() <= 0 || io_id.length() <= 0 || camera_ids.size() <= 0 || product_id.size() <= 0) {
		return false;
	}

	long max_lenght_of_camera = 0;

	SortCameraId(camera_ids);

	std::vector<std::string> string_for_encoding;
	std::vector<camera_info> cam_info;
	for (int i = 0; i < camera_ids.size(); i++) {
		cam_info.push_back(camera_info(PART_OK, camera_ids[i].first, camera_ids[i].second));
	}

	part_id hddId, _gu_id, ioId, _product_id;
	hddId.id = hdd_id;
	_gu_id.id = gu_id;
	ioId.id = io_id;
	_product_id.id = product_id;
	PrepareStringForEncoding(invoice_id, po_id, machine_id, hddId, _gu_id, ioId, cam_info, _product_id, string_for_encoding, date_time);
	FindNumbers(string_for_encoding);

	GetColors(color_hex_value1, color_hex_value2, qr_code_string);
return true;
// 	return GetQRImage(qr_code_string);
}

bool ValidateLicense(std::string &qr_code_string, std::string &invoice_id, std::string &po_id,
	long machine_id, std::string &hdd_id, std::string &gu_id, std::string &io_id,
	std::vector<std::pair<long, std::string>> &camera_ids, std::string &product_id,
	std::string &error_string, bool hdd_id_check, bool gu_id_check, bool io_id_check, bool camera_id_check, bool product_id_check) {

	if (hdd_id.length() <= 0 || gu_id.length() <= 0 || io_id.length() <= 0 || camera_ids.size() <= 0 || product_id.size() <= 0 || qr_code_string.length() <= 0) {
		return false;
	}

	long _machine_id;
	std::string _first_gen_date_time, _invoice_id, _po_id;
	part_id hddId, _gu_id, ioId, _product_id;
	std::vector<camera_info> _camera_ids;
	std::vector<part_renew_id> renewIds;
	std::vector<std::string> _color_hex_value1, _color_hex_value2;

	RetriveInfoFromQR(qr_code_string, _first_gen_date_time, _invoice_id, _po_id, _machine_id, hddId, _gu_id, ioId, _product_id,
		_camera_ids, renewIds, _color_hex_value1, _color_hex_value2);

// 	temp_qr_code_image.release();

	bool result = true;
	error_string.clear();
	error_string.append("LICENSE EXPIRED DUE TO\n");
	if (!StringMatching(_invoice_id, invoice_id)) {
		result = false;
		error_string.append("INVOICE NUMBER CHANGED\n");
	}
	if (!StringMatching(_po_id, po_id)) {
		result = false;
		error_string.append("PO NUMBER CHANGED\n");
	}
	if (_machine_id != machine_id) {
		result = false;
		error_string.append("MACHINE ID CHANGED\n");
	}

	if (hdd_id_check) {
		if (!StringMatching(hddId.id, hdd_id) || hddId.validity == PART_NOT_IN_USE) {
			bool id_matched = false;
			for (int i = 0; i < renewIds.size(); i++) {
				if (renewIds[i].id_type == HDD_INDEX && StringMatching(renewIds[i].id, hdd_id) && renewIds[i].validity == PART_OK) {
					id_matched = true;
				}
			}
			result = id_matched ? result : false;
			if (!id_matched) {
				error_string.append("HDD NUMBER CHANGED\n");
			}
		}
	}

	if (gu_id_check) {
		if (!StringMatching(_gu_id.id, gu_id) || _gu_id.validity == PART_NOT_IN_USE) {
			bool id_matched = false;
			for (int i = 0; i < renewIds.size(); i++) {
				if (renewIds[i].id_type == GU_INDEX && StringMatching(renewIds[i].id, gu_id) && renewIds[i].validity == PART_OK) {
					id_matched = true;
				}
			}
			result = id_matched ? result : false;
			if (!id_matched) {
				error_string.append("GUID NUMBER CHANGED\n");
			}
		}
	}

	if (io_id_check) {
		if (!StringMatching(ioId.id, io_id) || ioId.validity == PART_NOT_IN_USE) {
			bool id_matched = false;
			for (int i = 0; i < renewIds.size(); i++) {
				if (renewIds[i].id_type == IO_INDEX && StringMatching(renewIds[i].id, io_id) && renewIds[i].validity == PART_OK) {
					id_matched = true;
				}
			}
			result = id_matched ? result : false;
			if (!id_matched) {
				error_string.append("I/O SERIAL NUMBER CHANGED\n");
			}
		}
	}

	if (product_id_check){
		if (!StringMatching(_product_id.id, product_id) || _product_id.validity == PART_NOT_IN_USE) {
			bool id_matched = false;
			for (int i = 0; i < renewIds.size(); i++) {
				if (renewIds[i].id_type == PRODUCT_INDEX && StringMatching(renewIds[i].id, product_id) && renewIds[i].validity == PART_OK) {
					id_matched = true;
				}
			}
			result = id_matched ? result : false;
			if (!id_matched) {
				error_string.append("PRODUCT SELECTION CHANGED\n");
			}
		}
	}


	if (camera_id_check) {
		bool all_id_matched = true;
		if (camera_ids.size() <= 0) {
			result = false;
			error_string.append("NO CAMERA PRESENT\n");
		}
		for (int i = 0; i < camera_ids.size(); i++) {
			bool id_matched = false;
			//printf("CAMERA ID %s\n", camera_ids[i].second);
			for (int j = 0; j < _camera_ids.size(); j++) {
				//printf("LIC ID %s\n", _camera_ids[j].camera_id);
				if (_camera_ids[j].validity_id == PART_OK) {
					if (StringMatching(_camera_ids[j].camera_id, camera_ids[i].second) && _camera_ids[j].station_id == camera_ids[i].first) {
						id_matched = true;
					}
				}
			}
			if (!id_matched){
				for (int j = 0; j < renewIds.size(); j++) {
					//printf("LICRENEW ID %s\n", renewIds[j].id);
					if (renewIds[j].id_type == CAM_INDEX && renewIds[j].validity == PART_OK) {
						if (StringMatching(renewIds[j].id, camera_ids[i].second) && renewIds[j].station_id == camera_ids[i].first) {
							id_matched = true;
						}
					}
				}
			}
			all_id_matched = (!id_matched || !all_id_matched) ? false : true;
		}

		if (!all_id_matched) {
			result = false;
			error_string.append("CAMERA SERIAL NUMBER OR STATION INDEX NOT MATCHING\n");
		}
	}

	if (result) {
		error_string.clear();
	}
	return result;
}












std::string getDataFromQr(std::string string1) {

    std::string qr_string;
    std::string first_gen_date_time;
    std::string invoice_id;
    std::string po_id;
    long machine_id;
    part_id hdd_id;
    part_id gu_id;
    part_id io_id;
    part_id product_id;
    std::vector<camera_info> camera_ids;
    std::vector<part_renew_id> renew_ids;
    std::vector<std::string> color_hex_value1, color_hex_value2;

    qr_string = string1;

    Initialize();
    bool RenewLicense(std::string &qr_string, long machine_id, std::string &hdd_id, std::string &gu_id, std::string &io_id,
		std::vector<std::pair<long, std::string>> &camera_ids, std::string &product_id,
		std::vector<std::string> &color_hex_value1, std::vector<std::string> &color_hex_value2,
		 std::string &qr_code_string, const std::string &date_time = "");

	bool GetLicense(std::string &invoice_id, std::string &po_id, long machine_id, std::string &hdd_id, std::string &gu_id, std::string &io_id,
		std::vector<std::pair<long, std::string>> &camera_ids, std::string &product_id,
		std::vector<std::string> &color_hex_value1, std::vector<std::string> &color_hex_value2,
		 std::string &qr_code_string, const std::string &date_time = "");



	bool ValidateLicense(std::string &qr_code_string, std::string &invoice_id, std::string &po_id, long machine_id, std::string &hdd_id, std::string &gu_id, std::string &io_id,
		std::vector<std::pair<long, std::string>> &camera_ids, std::string &product_id, std::string &error_string,
		bool hdd_id_check = true, bool gu_id_check = true, bool io_id_check = true, bool camera_id_check = true, bool product_id_check = true);


    std::string result = RetriveInfoFromQR(qr_string, first_gen_date_time, invoice_id, po_id,
                                           machine_id, hdd_id, gu_id, io_id,
                                           product_id, camera_ids, renew_ids,
                                           color_hex_value1, color_hex_value2);

    std::string lic_info = "";
    std::string cameraProduct = "";
    lic_info.append("PRIMARY INFORMATION");
    lic_info.append("\nDATE : " + first_gen_date_time);
    lic_info.append("\nMACHINE : " + GetMachineName(machine_id));
    lic_info.append("\nHDD : " + std::to_string(hdd_id.validity) + " " + hdd_id.id);
    lic_info.append("\nGU : " + std::to_string(gu_id.validity) + " " + gu_id.id);
    lic_info.append("\nIO : " + std::to_string(io_id.validity) + " " + io_id.id);
    lic_info.append("\nPRODUCT : " + std::to_string(product_id.validity) + " " + product_id.id);

    lic_info.append("\nPRODUCT NO : "
                    + getProductNumber(product_id.id));
    std::string final_key = "";
    for (int i = 0; i < color_hex_value2.size(); i++) {
        final_key += std::string(color_hex_value2.at(i).c_str());
        if (i < color_hex_value2.size() - 1) {
            final_key += " - ";
        }
    }
    lic_info.append(
            "\nShort-Key : " + final_key);
    lic_info.append(result);
    for (int i = 0; i < camera_ids.size(); i++) {
        lic_info.append("\nCAMERA : " + std::to_string(camera_ids[i].validity_id) + " " +
                        std::to_string(camera_ids[i].station_id) + " " + camera_ids[i].camera_id);
    }

    std::string product_code = "";
    if (product_id.validity == PART_OK) {
        product_code = product_id.id;
    }


    if (renew_ids.size() > 0) {
        //User $!$ for split secondary information

        lic_info.append("\n\nSECONDARY INFORMATION");
        for (int i = 0; i < renew_ids.size(); i++) {
            if (renew_ids[i].id_type == HDD_INDEX) {
                lic_info.append(
                        "\nHDD : " + std::to_string(renew_ids[i].validity) + " " + renew_ids[i].id +
                        " " + renew_ids[i].date);
            } else if (renew_ids[i].id_type == GU_INDEX) {
                lic_info.append(
                        "\nGU : " + std::to_string(renew_ids[i].validity) + " " + renew_ids[i].id +
                        " " + renew_ids[i].date);
            } else if (renew_ids[i].id_type == IO_INDEX) {
                lic_info.append(
                        "\nIO : " + std::to_string(renew_ids[i].validity) + " " + renew_ids[i].id +
                        " " + renew_ids[i].date);
            } else if (renew_ids[i].id_type == PRODUCT_INDEX) {
                lic_info.append("\nPRODUCT : " + std::to_string(renew_ids[i].validity) + " " +
                                renew_ids[i].id + " " + renew_ids[i].date);
                if (renew_ids[i].validity == PART_OK) {
                    product_code = renew_ids[i].id;
                }
                lic_info.append("\nPRODUCT NO : " + renew_ids[i].date + "$"
                                + getProductNumber(renew_ids[i].id));
            } else if (renew_ids[i].id_type == CAM_INDEX) {
                lic_info.append("\nCAMERA : " + std::to_string(renew_ids[i].validity) + " " +
                                std::to_string(renew_ids[i].station_id) + " " + renew_ids[i].id +
                                " " + renew_ids[i].date);
            }
        }
    }

    printf("%s", lic_info.c_str());

    // printf("\n\nFinal-Key : ");
    // for (int i = 0; i < color_hex_value2.size(); i++) {
    //     printf("\t%s", color_hex_value2[i].c_str());
    // }


    // printf("%s", lic_info.c_str());
    return lic_info;

}



