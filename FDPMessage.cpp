//
// Created by seaskyways on 9/14/17.
//

#include <bits/types.h>
#include <cstring>
#include <vector>
#include <string>
#include "FDPMessage.h"

namespace fdp {
    class FDPMessage {
    public:
        static const char *parse(const char *string) {
            //region Extract the event from the beginning, max is 4 bytes
            auto event = (__uint32_t) string[0];
            unsigned int i = 1;
            while (string[i] != ':') {
                event = (event << 8) | string[i];
                i++;
            }
            //endregion
            //region Extract sender name
            i++;
            auto nameStart = i;
            auto namePtr = &string[i];
            for (; string[i] != ':' || (string[i - 1] == '\\' && string[i - 2] != '\\'); i++) {
            }
            unsigned int size = i - nameStart;
            auto name = (const char *) (calloc(size, sizeof(char)));
            memcpy((void *) name, namePtr, size);
            //endregion
            i++;
            auto dataStart = i;
            auto dataPtr = &string[i];
            for (; string[i] != '#' || (string[i - 1] == '\\' && string[i - 2] != '\\'); i++) {
            }
            size = i - dataStart;
            auto data = (const char *) (calloc(size, sizeof(char)));
            memcpy((void *) data, dataPtr, size);

            return data;
        }

    public:
        FDPMessage(__uint32_t event, const char *name, const char *data) :
                event(event),
                name(name),
                data(data) {}

    private:
        __uint32_t event;
        const char *name;
        const char *data;

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
    };
}