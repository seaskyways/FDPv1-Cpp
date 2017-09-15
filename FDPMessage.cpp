//
// Created by seaskyways on 9/14/17.
//

#include <bits/types.h>
#include <cstring>
#include <string>
#include <map>
#include "FDPMessage.h"

namespace fdp {
    using namespace std;
    typedef const char *c_str;

    class FDPMessage {
    public:
        static FDPMessage *parse(c_str str) {
            //region Extract the event from the beginning, max is 4 bytes
            auto event = (__uint32_t) str[0];
            uint32_t i = 1;
            while (str[i] != ':') {
                event = (event << 8) | str[i];
                i++;
            }
            //endregion
            i++;
            const auto name = extractEscapedString(str, &i, ':');
            i++;
            const auto data = extractEscapedString(str, &i, '#');

            map<c_str, c_str> options;
            if (str[i] == '#') {
                while (str[i] != 0) {
                    i++;
                    const auto optName = extractEscapedString(str, &i, '=', '#');
                    if (__glibc_likely(str[i] == '=')) {
                        i++;
                        const auto optValue = extractEscapedString(str, &i, '#');
                        options.insert(pair<c_str, c_str>(optName, optValue));
                    } else {
                        options.insert(pair<c_str, c_str>(optName, ""));
                    }
                }
            }

            return new FDPMessage(event, name, data, options);
        }

//        const char *to_string(uint32_t event, c_str name, c_str data, const map<c_str, c_str> &options) {
//            auto str = new string();
//            char eventBytes[sizeof(uint32_t)];
//        }

    private:
        /** extracts the data from start till character considering escapes using \
         *  It leaved the pointer i at the index the character is found
         * */
        static const char *extractEscapedString(
                const char *str,
                __uint32_t *i,
                const char tillCharacter,
                const char tillCharacter2 = 0
        ) {
            const uint32_t start = *i;
            for (; ((str[*i] != tillCharacter && str[*i] != tillCharacter2)
                    && str[*i] != 0) ||
                   (str[*i - 1] == '\\' && str[*i - 2] != '\\');
                   (*i)++) {
            }
            auto size = *i - start;
            auto result = (char *) calloc(size, sizeof(char));
            memcpy((void *) result, &str[start], size);
            return result;
        }

    public:
        FDPMessage(__uint32_t event, const char *name, const char *data, map<c_str, c_str> options) :
                event(event),
                name(name),
                data(data),
                options(std::move(options)) {}

    private:
        __uint32_t event;
        const char *name;
        const char *data;
        map<c_str, c_str> options;

    public:
        const __uint32_t getEvent() const {
            return event;
        }

        const char *getName() const {
            return name;
        }

        const char *getData() const {
            return data;
        }

        const map<c_str, c_str> getOptions() const {
            return options;
        };
    };
}